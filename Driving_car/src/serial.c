#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/sys/printk.h>
#include <string.h>
#include "serial.h"
#include "motor_controls.h"
#include "pwm.h"
#include "gatekeeper.h"

static const struct device *uart_dev = DEVICE_DT_GET(DT_NODELABEL(uart1));
static char rx_buffer[128];
static int rx_pos = 0;
static int current_speed = 100;
static char last_command = 'A'; 

static void serial_cb(const struct device *dev, void *user_data){
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

int Serial_begin(void){
    if (!device_is_ready(uart_dev)) {
        printk("Error: UART device not ready.\n");
        return -1;
    }

    uart_irq_callback_user_data_set(uart_dev, serial_cb, NULL);
    uart_irq_rx_enable(uart_dev);
    
    return 0;
}

void uart_send_str(const char *str){
    for (int i = 0; i < strlen(str); i++) {
        uart_poll_out(uart_dev, str[i]);
    }
}
void execute_serial_last_action(){
    process_serial_command(&last_command);
}

void process_serial_command(char* serial_command){
    int len = strlen(serial_command);


    if(strcmp(serial_command, "FORWARD") == 0 || strcmp(serial_command, "F") == 0){
        last_command = 'F';
    }
    else if(strcmp(serial_command, "BACKWARD") == 0 || strcmp(serial_command, "B") == 0){
        last_command = 'B';
    }
    else if(strcmp(serial_command, "LEFT") == 0 || strcmp(serial_command, "L") == 0){
        last_command = 'L';
    }
    else if(strcmp(serial_command, "RIGHT") == 0 || strcmp(serial_command, "R") == 0){
        last_command = 'R';
    }
    else if(strcmp(serial_command, "STOP") == 0 || strcmp(serial_command, "S") == 0){
        last_command = 'S';
    }
    else if(strcmp(serial_command, "ROTATE_RIGHT") == 0 || strcmp(serial_command, "RR") == 0){
        last_command = 'r';
    }
    else if(strcmp(serial_command, "ROTATE_LEFT") == 0 || strcmp(serial_command, "RL") == 0){
        last_command = 'l';
    }
    else if(strncmp(serial_command, "SPEED ", 6) == 0){
        int new_speed = atoi(serial_command + 6);
        if(new_speed >=0 && new_speed <=100){
            current_speed = new_speed;
        }else{
            current_speed = 100;
            printk("INvalid SPEED value. Setting speed to 100%%. \n");
        }
    }

    if(bluetouth_in_control()){
        return;
    }

    if(last_command == 'F'){
        Drive_motors(Forward, current_speed);
    }
    else if(last_command == 'B'){
        Drive_motors(Backward, current_speed);
    }
    else if(last_command == 'L'){
        Drive_motors(Left, current_speed);
    }
    else if(last_command == 'R'){
        Drive_motors(Right, current_speed);
    }
    else if(last_command == 'S'){
        Stop_motors();
    }
    else if(last_command == 'r'){
        Drive_motors(Rotate_Right, current_speed);
    }
    else if(last_command == 'l'){
        Drive_motors(Rotate_Left, current_speed);
    }
    else{
        printk("Unknown command: %s\n", serial_command);
    }
}







