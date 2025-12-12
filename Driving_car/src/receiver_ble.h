// This File has been writen by Wang King Son
// link to his github: https://github.com/WangKKing3

#ifndef RECEIVER_BLE_H
#define RECEIVER_BLE_H

#include <stdint.h>
#include <stdbool.h>
#include "motor_controls.h"


typedef void (*drive_callback_t)(Motor_direction dir, uint8_t speed);

int ble_init(drive_callback_t cb);
int ble_start_scan(void);
bool ble_is_connected(void);

#endif