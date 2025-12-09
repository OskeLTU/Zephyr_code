#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/sys/printk.h>
#include <string.h>
#include "serial.h"
#include "motor_controls.h"
#include "pwm.h"

static const struct device *uart_dev = DEVICE_DT_GET(DT_NODELABEL(uart1));
static char rx_buffer[128];
static int rx_pos = 0;

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
                
                process_serial_command(rx_buffer);
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



int Serial_begin(void)
{
    if (!device_is_ready(uart_dev)) {
        printk("Error: UART device not ready.\n");
        return -1;
    }

    uart_irq_callback_user_data_set(uart_dev, serial_cb, NULL);
    uart_irq_rx_enable(uart_dev);
    
    return 0;
}

void uart_send_str(const char *str)
{
    for (int i = 0; i < strlen(str); i++) {
        uart_poll_out(uart_dev, str[i]);
    }
}

void process_serial_command(char* serial_command){
    int len = strlen(serial_command);

    if(strcmp(serial_command, "FORWARD") == 0){
        Drive_motors(Forward, 100);
    }
    else if(strcmp(serial_command, "BACKWARD") == 0){
        Drive_motors(Backward, 100);
    }
    else if(strcmp(serial_command, "LEFT") == 0){
        Drive_motors(Left, 100);
    }
    else if(strcmp(serial_command, "RIGHT") == 0){
        Drive_motors(Right, 100);
    }
    else if(strcmp(serial_command, "STOP") == 0){
        Stop_motors();
    }
    else{
        printk("Unknown command: %s\n", serial_command);
    }
}