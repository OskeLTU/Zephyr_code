#ifndef motor_controls_h
#define motor_controls_h

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/kernel.h>

enum Motror {
    motor_dir_froward,
    motor_dir_backward,
    motor_dir_stop
};

struct Motor {
    const struct gpio_dt_spec *in1;
    const struct gpio_dt_spec *in2;
    const struct pwm_dt_spec *speed_pwm;
} notor_t;

void motor_init(const struct Motor* motor);

void motor_set_speed(const struct Motor* motor, int speed_percentage);

void motor_stop(const struct Motor* motor);

#endif // motor_controls_h