// Receiver over BLRE - receives Motor_direction commands via BLE notifications
// This File has been writen by Wang King Son
// link to his github: https://github.com/WangKKing3

#include "receiver_ble.h"
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <string.h>

#define DRIVE_SVC_UUID \
    BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef0)
#define DRIVE_CHR_UUID \
    BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef1)

static struct bt_uuid_128 svc_uuid = BT_UUID_INIT_128(DRIVE_SVC_UUID);
static struct bt_uuid_128 chr_uuid = BT_UUID_INIT_128(DRIVE_CHR_UUID);
static struct bt_uuid *ccc_uuid = BT_UUID_GATT_CCC;

static struct bt_gatt_discover_params disc_params;
static struct bt_gatt_subscribe_params sub_params;
static struct bt_conn *conn;
static drive_callback_t user_cb;

/* Packet struct - må matche sender */
struct drive_packet {
    uint8_t direction;
    uint8_t speed;
} __packed;

/* Reconnect */
static void rescan_work_fn(struct k_work *work);
K_WORK_DELAYABLE_DEFINE(rescan_work, rescan_work_fn);

static void rescan_work_fn(struct k_work *work)
{
    if (!conn) ble_start_scan();
}

/* Notification */
static uint8_t on_notify(struct bt_conn *c, struct bt_gatt_subscribe_params *p,
                         const void *buf, uint16_t len)
{
    if (!buf) return BT_GATT_ITER_STOP;

    if (len == sizeof(struct drive_packet) && user_cb) {
        const struct drive_packet *pkt = buf;
        user_cb((Motor_direction)pkt->direction, pkt->speed);
    }
    return BT_GATT_ITER_CONTINUE;
}

/* Discovery */
static uint8_t on_discover(struct bt_conn *c, const struct bt_gatt_attr *attr,
                           struct bt_gatt_discover_params *p)
{
    if (!attr) return BT_GATT_ITER_STOP;

    if (p->uuid == &svc_uuid.uuid) {
        disc_params.uuid = &chr_uuid.uuid;
        disc_params.start_handle = attr->handle + 1;
        disc_params.type = BT_GATT_DISCOVER_CHARACTERISTIC;
        bt_gatt_discover(c, &disc_params);
    } else if (p->uuid == &chr_uuid.uuid) {
        disc_params.uuid = ccc_uuid;
        disc_params.start_handle = attr->handle + 2;
        disc_params.type = BT_GATT_DISCOVER_DESCRIPTOR;
        sub_params.value_handle = attr->handle + 1;
        bt_gatt_discover(c, &disc_params);
    } else {
        sub_params.notify = on_notify;
        sub_params.value = BT_GATT_CCC_NOTIFY;
        sub_params.ccc_handle = attr->handle;
        int err = bt_gatt_subscribe(c, &sub_params);
        if (!err || err == -EALREADY) {
            printk("Subscribed - READY!\n");
        }
    }
    return BT_GATT_ITER_STOP;
}

/* Scan */
static void on_device_found(const bt_addr_le_t *addr, int8_t rssi, uint8_t type,
                            struct net_buf_simple *ad)
{
    if (conn || type != BT_GAP_ADV_TYPE_ADV_IND) return;

    while (ad->len > 1) {
        uint8_t len = net_buf_simple_pull_u8(ad);
        if (len == 0 || len > ad->len) return;
        uint8_t ad_type = net_buf_simple_pull_u8(ad);

        if (ad_type == BT_DATA_UUID128_ALL && len == 17) {
            if (!memcmp(ad->data, svc_uuid.val, 16)) {
                printk("Found joystick (RSSI %d)\n", rssi);
                bt_le_scan_stop();
                int err = bt_conn_le_create(addr, BT_CONN_LE_CREATE_CONN,
                                            BT_LE_CONN_PARAM_DEFAULT, &conn);
                if (err) k_work_schedule(&rescan_work, K_MSEC(500));
                return;
            }
        }
        net_buf_simple_pull(ad, len - 1);
    }
}

/* Connection */
static void on_connected(struct bt_conn *c, uint8_t err)
{
    if (err) {
        printk("Connect failed: %d\n", err);
        if (conn) { bt_conn_unref(conn); conn = NULL; }
        k_work_schedule(&rescan_work, K_MSEC(200));
        return;
    }
    printk("Connected\n");

    disc_params.uuid = &svc_uuid.uuid;
    disc_params.func = on_discover;
    disc_params.start_handle = BT_ATT_FIRST_ATTRIBUTE_HANDLE;
    disc_params.end_handle = BT_ATT_LAST_ATTRIBUTE_HANDLE;
    disc_params.type = BT_GATT_DISCOVER_PRIMARY;
    bt_gatt_discover(conn, &disc_params);
}

static void on_disconnected(struct bt_conn *c, uint8_t reason)
{
    printk("Disconnected: 0x%02x\n", reason);
    if (conn) { bt_conn_unref(conn); conn = NULL; }
    k_work_schedule(&rescan_work, K_MSEC(100));
}

static struct bt_conn_cb conn_cb = {
    .connected = on_connected,
    .disconnected = on_disconnected,
};

/* Public API */
int ble_init(drive_callback_t cb)
{
    user_cb = cb;
    int err = bt_enable(NULL);
    if (err) return err;
    printk("Bluetooth ready\n");
    bt_conn_cb_register(&conn_cb);
    return 0;
}

int ble_start_scan(void)
{
    if (conn) return 0;
    printk("Scanning...\n");
    return bt_le_scan_start(BT_LE_SCAN_PASSIVE, on_device_found);
}

bool ble_is_connected(void)
{
    return conn != NULL;
}