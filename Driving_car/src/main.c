#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>

static const struct gpio_dt_spec mototr_a_in1 = GPIO_DT_SPEC_GET(DT_NODELABEL(mototr_a_in1), gpios);
static const struct gpio_dt_spec mototr_a_in2 = GPIO_DT_SPEC_GET(DT_NODELABEL(mototr_a_in2), gpios);
static const struct gpio_dt_spec mototr_b_in1 = GPIO_DT_SPEC_GET(DT_NODELABEL(mototr_b_in1), gpios);
static const struct gpio_dt_spec mototr_b_in2 = GPIO_DT_SPEC_GET(DT_NODELABEL(mototr_b_in2), gpios);

static const struct pwm_dt_spec motor_speed_a = DEVICE_DT_GET(DT_NODELABEL(motor_speed_a));
static const struct pwm_dt_spec motor_speed_b = DEVICE_DT_GET(DT_NODELABEL(motor_speed_b));

int main(void)
{
    
}
