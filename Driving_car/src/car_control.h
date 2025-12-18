/*
* Author: Wang King Son
* Link to his github: https://github.com/WangKKing3
* 
* Acknowledgement:
* This file does use the motor_controls, pwm, and gatekeeper libraries that were produced by Oskaras Dauneckas
*/

#ifndef CAR_CONTROLLER_H
#define CAR_CONTROLLER_H

#include <stdint.h>

int car_controller_init(void);

void car_controller_start(void);

void car_controller_check_timeout(void);
#endif