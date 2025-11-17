#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include <stdint.h>
#include "pwm.h"
#include "motor_controls.h"



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

    Drive_one_motor(Motor_A_Front, Forward, 100);
    Drive_one_motor(Motor_B_Front, Forward, 100);

    // Drive_one_motor(Motor_A_Back, Forward, 100);
    // Drive_one_motor(Motor_B_Back, Forward, 100);

    
    return 0;
}

