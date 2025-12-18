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


int main(void){

    pwm_begin();
    motors_start();
    // Drive_motors(Forward, 50);
    // while(1){
    // Drive_motors(Forward, 100);
    // k_msleep(5000);
    // printk("reached flag 1\n");
    // Stop_motors();
    // k_msleep(2000);
    // printk("reached flag 2\n");
    // Drive_motors(Forward, 50);
    // k_msleep(5000);
    // Stop_motors();
    // }
    while(1){
       Drive_motors(Forward, 100);
       k_msleep(2000);
         Stop_motors();
         k_msleep(2000);
         Drive_motors(Backward, 100);
            k_msleep(2000);
            Stop_motors();
            k_msleep(2000);
            Drive_motors(Forward, 50);
            k_msleep(2000);
            Stop_motors();
            k_msleep(2000);
            Drive_motors(Backward, 50);
               k_msleep(2000);
                Stop_motors();
                k_msleep(2000);
    }

    Drive_one_motor(Motor_A_Front, Backward, 100);
    Drive_one_motor(Motor_B_Front, Backward, 100);

    Drive_one_motor(Motor_A_Back, Backward, 100);
    Drive_one_motor(Motor_B_Back, Backward, 100);

    
    return 0;
}

// int main(){
//     Serial_begin();
//     uart_send_str("F\n");
//     printk("Sent\n");
//     return 0;
// }