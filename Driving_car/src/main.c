#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include <stdint.h>
#include "pwm.h"
#include "motor_controls.h"
#include "serial.h"
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>


int main(void)
{
    Serial_begin();
    motors_start();
    while (1) {
        uart_send_str("BACKWARD\n");
    }

    return 0;
}