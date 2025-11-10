#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include <stdint.h>

#include "pwm.h"
#include "motor_controls.h"

static const struct gpio_dt_spec motor_a_in1 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in1), gpios);
static const struct gpio_dt_spec motor_a_in2 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in2), gpios);
static const struct gpio_dt_spec motor_a_in3 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in3), gpios);
static const struct gpio_dt_spec motor_a_in4 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in4), gpios);

static const struct gpio_dt_spec motor_b_in1 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in1), gpios);
static const struct gpio_dt_spec motor_b_in2 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in2), gpios);
static const struct gpio_dt_spec motor_b_in3 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in3), gpios);
static const struct gpio_dt_spec motor_b_in4 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in4), gpios);

typedef struct {
    const struct gpio_dt_spec *in1;
    const struct gpio_dt_spec *in2;
    int (*pwm_write)(uint32_t value);
} motor_channel_t;

static const motor_channel_t motors[] = {
    {&motor_a_in1, &motor_a_in2, pwm_write_front_a},
    {&motor_a_in3, &motor_a_in4, pwm_write_front_b},
    {&motor_b_in1, &motor_b_in2, pwm_write_back_a},
    {&motor_b_in3, &motor_b_in4, pwm_write_back_b}
};

static uint32_t percentage_to_pwm(uint32_t speed_percentage){
    if(speed_percentage > 100){
        speed_percentage = 100;
    }
    return (speed_percentage * 255) / 100;
}

int motors_start(){
    const struct gpio_dt_spec *gpio_pins[] = {
        &motor_a_in1, &motor_a_in2,
        &motor_a_in3, &motor_a_in4,
        &motor_b_in1, &motor_b_in2,
        &motor_b_in3, &motor_b_in4

    };
    int check = 0;

    for(size_t i = 0; i < ARRAY_SIZE(gpio_pins); i++){
        if (!gpio_is_ready_dt(gpio_pins[i])){
            printk("Error: One or more GPIO devices not ready.\n");
            return -1;
        }
        int check = gpio_pin_configure_dt(gpio_pins[i], GPIO_OUTPUT_INACTIVE);
        if(check < 0){
            printk("Error: Failed to configure GPIO pin %d.\n", i);
            return -1;
        }
    }

    if(pwm_begin() != 0){
        return -1;
    }
    return 0;
}

void Drive_one_motor(Motor_name motor, Motor_direction direction, uint32_t speed_percentage){
    if(motor >= ARRAY_SIZE(motors)){
        printk("Error: Invalid motor selection.\n");
        return; 
    }
    const motor_channel_t *selected_motor = &motors[motor];
    uint32_t pwm_value = percentage_to_pwm(speed_percentage);

    switch (direction){
        case Forward:
            gpio_pin_set_dt(selected_motor->in1, 1);
            gpio_pin_set_dt(selected_motor->in2, 0);
            break;
        case Backward:
            gpio_pin_set_dt(selected_motor->in1, 0);
            gpio_pin_set_dt(selected_motor->in2, 1);
            break;
        case Stop:
            gpio_pin_set_dt(selected_motor->in1, 0);
            gpio_pin_set_dt(selected_motor->in2, 0);
            pwm_value = 0;
            break;
        default:
            gpio_pin_set_dt(selected_motor->in1, 0);
            gpio_pin_set_dt(selected_motor->in2, 0);
            pwm_value = 0;
            break;
    }
    if(selected_motor->pwm_write(pwm_value) != 0){
    printk("Error: Failed to set PWM for motor %d.\n", motor);
    }
}

void Drive_motors(Motor_direction direction, uint32_t speed_percentage){
    if(direction == Stop){
        Stop_motors();
        return;
    }

    Drive_one_motor(Motor_A_Front, direction, speed_percentage);
    Drive_one_motor(Motor_A_Back, direction, speed_percentage);
    Drive_one_motor(Motor_B_Front, direction, speed_percentage);
    Drive_one_motor(Motor_B_Back, direction, speed_percentage);
}

void Stop_motors(){
    Drive_one_motor(Motor_A_Front, Stop, 0);
    Drive_one_motor(Motor_A_Back, Stop, 0);
    Drive_one_motor(Motor_B_Front, Stop, 0);
    Drive_one_motor(Motor_B_Back, Stop, 0);
}