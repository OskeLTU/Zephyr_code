#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include <stdint.h>
#include "pwm.h"
#include "motor_controls.h"
#include "serial.h"
#include "gatekeeper.h"
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include "car_control.h"

int main(void)
{
    motors_start();
    Serial_begin(); 
    car_controller_init();

    while (1) {


        car_controller_check_timeout();
        k_msleep(100);
    };
    return 0;
}

