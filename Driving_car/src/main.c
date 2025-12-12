// Group project for Smart Systems 2025


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
    
    Serial_begin(); 
    car_controller_init();
    car_controller_start();

    while (1) {


        car_controller_check_timeout();
        timeout_control();
        k_msleep(50);
    };
    return 0;
}

// int main(){
//     Serial_begin();
//     uart_send_str("F\n");
//     printk("Sent\n");
//     return 0;
// }