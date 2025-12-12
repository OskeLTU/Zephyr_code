// This File has been writen by Wang King Son
// link to his github: https://github.com/WangKKing3

#ifndef CAR_CONTROLLER_H
#define CAR_CONTROLLER_H

#include <stdint.h>

int car_controller_init(void);

void car_controller_start(void);

void car_controller_check_timeout(void);
#endif