#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

static const struct gpio_dt_spec my_led = GPIO_DT_SPEC_GET(DT_NODELABEL(external_led_0), gpios);

int main(void)
{
    gpio_pin_configure_dt(&my_led, GPIO_OUTPUT_ACTIVE);

    while (1) {
        gpio_pin_set_dt(&my_led, 1);
        k_msleep(500);
        gpio_pin_set_dt(&my_led, 0);
        k_msleep(500);
    }
}
