#include <stdint.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <stdio.h>
#include "pwm.h"
static const struct device *front_a_speed;


int pwm_begin(){
    front_a_speed = device_get_binding("PWM_0");


    if (front_a_speed == NULL ){
        printk("Error: One or more PWM devices not found.\n");
        return -1; // PWM devices not found
    }else{
        printk("All PWM devices are ready.\n");
        return 0; // All PWM devices ready
    }
}

int pwm_write(uint32_t value){
    return pwm_set(front_a_speed, 0, pwm_period_ns, value, 0) ;
}