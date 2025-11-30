#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <bluetooth/services/nus.h>

#include "bluetooth.h"
#include "motor_controls.h" // Access to Drive_motors()

static struct bt_conn_cb conn_callback = {
    .connected = connected;
    .disconnected = disconnected;
}

//function for bluetooth signal{
void bt_recive_cb(struct bt_conn *conn, const uint8_t *const data, uint16_t len){
    if (len == 0) {
        return;
    }
    if(command == 'M'){
        manual_overide_flag = !manual_overide_flag;

        if(manual_overide_flag){
            printk("Manual_mode_enabled\n");
        }else{
            printk("manual_mode_disabled\n");
        }
        return;
    }

    if(!manual_overide_flag){
        return;
    }

    switch(command){
        case 'F':
            Drive_motors(Forward, 100);
            break;
        case 'B':
            Drive_motors(Backward, 100);
            break;
        case 'L':
            Drive_motors(Left, 100);
            break;
        case 'R':
            Drive_motors(Right, 100);
            break;
        case 'S':
            Stop_motors();
            break;
        default:
        break;
    }
}


