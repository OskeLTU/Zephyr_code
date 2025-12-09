#ifndef SERIAL_H
#define SERIAL_H

int Serial_begin();
void uart_send_str(const char *str);
void process_serial_command(char* serial_command);

#endif