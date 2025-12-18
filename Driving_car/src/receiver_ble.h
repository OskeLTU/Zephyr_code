/*
* Author: Wang King Son
* Link to his github: https://github.com/WangKKing3
* 
* Acknowledgement:
* This file includes example code derrived from the Zephyr Project 
* Pong sample
*/

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