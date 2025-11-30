#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include <stdint.h>
#include "pwm.h"
#include "motor_controls.h"

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>

/* Get the I2C device pointer */
static const struct device *const i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c1));

#define TARGET_ADDR 0x42

int main(void)
{
    printk("--- I2C Sender Starting ---\n");

    /* Check if the device driver was initialized */
    if (!device_is_ready(i2c_dev)) {
        printk("Error: I2C device not ready.\n");
        return 0;
    }

    uint8_t data = 0;

    while (1) {
        printk("Sending data: %d... ", data);

        /* Master write to target */
        int ret = i2c_write(i2c_dev, &data, 1, TARGET_ADDR);

        if (ret == 0) {
            printk("ACK received!\n");
        } else {
            printk("Error %d (No ACK?)\n", ret);
        }

        data++;
        k_msleep(2000);
    }
    return 0;
}
