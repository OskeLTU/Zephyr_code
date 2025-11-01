#include <stdint.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <stdio.h>
#include "pwm.h"
static const struct device *front_a_speed;
static const struct device *front_b_speed;
static const struct device *back_a_speed;
static const struct device *back_b_speed;

int pwm_begin(){
    front_a_speed = device_get_binding("PWM_0");
    front_b_speed = device_get_binding("PWM_1");
    back_a_speed = device_get_binding("PWM_2");
    back_b_speed = device_get_binding("PWM_3");

    if (front_a_speed == NULL || front_b_speed == NULL || back_a_speed == NULL || back_b_speed == NULL){  
        printk("Error: One or more PWM devices not found.\n");
        return -1; // PWM devices not found
    }else{
        printk("All PWM devices are ready.\n");
        return 0; // All PWM devices ready
    }
}

int pwm_write_front_a(uint32_t value) {
    return pwm_set(front_a_speed, 0, pwm_period_ns, value, 0);
}

int pwm_write_front_b(uint32_t value) {
    return pwm_set(front_b_speed, 1, pwm_period_ns, value, 0);
}

int pwm_write_back_a(uint32_t value) {
    return pwm_set(back_a_speed, 2, pwm_period_ns, value, 0);
}

int pwm_write_back_b(uint32_t value) {
    return pwm_set(back_b_speed, 3, pwm_period_ns, value, 0);
}
