#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include <stdint.h>
#include "pwm.h"
#include "motor_controls.h"
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>

const struct device *uart_dev = DEVICE_DT_GET(DT_NODELABEL(uart1));
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);


static char rx_buffer[128]; 
static int rx_pos = 0;     

void uart_send_str(const struct device *dev, const char *str)
{
    for (int i = 0; i < strlen(str); i++) {
        uart_poll_out(dev, str[i]);
    }
}

static void serial_cb(const struct device *dev, void *user_data)
{
    uint8_t c;

    if (!uart_irq_update(dev)) return;
    if (!uart_irq_rx_ready(dev)) return;
    while (uart_fifo_read(dev, &c, 1) == 1) {
        if (c == '\n' || c == '\r') {
            rx_buffer[rx_pos] = '\0'; 
            
            if (rx_pos > 0) {
                printk("Received Message: %s\n", rx_buffer);
            }
            
            rx_pos = 0; 
        }
        else {
            if (rx_pos < sizeof(rx_buffer) - 1) {
                rx_buffer[rx_pos++] = c;
            }
        }
    }
}

int main(void)
{
    printk("--- String Chat Ready (Pins 0/1) ---\n");

    if (!device_is_ready(uart_dev) || !gpio_is_ready_dt(&button)) {
        printk("Error: Devices not ready.\n");
        return 0;
    }

    uart_irq_callback_user_data_set(uart_dev, serial_cb, NULL);
    uart_irq_rx_enable(uart_dev);
    gpio_pin_configure_dt(&button, GPIO_INPUT);

    printk("Press Button A to send a text string!\n");

    while (1) {
        if (gpio_pin_get_dt(&button)) {
            
            printk("Sending: 'Hello World!'\n");

            uart_send_str(uart_dev, "Hello World!\r\n");

            k_sleep(K_MSEC(500)); 
        }
        k_sleep(K_MSEC(100));
    }
    return 0;
}