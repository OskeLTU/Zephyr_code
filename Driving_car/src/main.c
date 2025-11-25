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

    Drive_motors(Forward, 50);

    
    return 0;
}

