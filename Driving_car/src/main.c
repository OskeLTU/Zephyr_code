#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>

static const struct gpio_dt_spec motor_a_in1 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in1), gpios);
static const struct gpio_dt_spec motor_a_in2 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in2), gpios);
static const struct gpio_dt_spec motor_b_in1 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in1), gpios);
static const struct gpio_dt_spec motor_b_in2 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in2), gpios);



static const struct pwm_dt_spec motor_a_speed = PWM_DT_SPEC_GET(DT_NODELABEL(motor_a_speed));
static const struct pwm_dt_spec motor_b_speed = PWM_DT_SPEC_GET(DT_NODELABEL(motor_b_speed));

int main(void)
{
    
}
