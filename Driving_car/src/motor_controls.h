#ifndef MOTOR_CONTROLS_H
#define MOTOR_CONTROLS_H

typedef enum {
    Forward,
    Backward,
    Stop
}Motor_direction;

typedef enum{
    Motor_A_Front,
    Motor_A_Back,
    Motor_B_Front,
    Motor_B_Back
}Motor_name;

int motors_start();

void Drive_one_motor(Motor_name motor, Motor_direction direction, uint32_t speed_percentage);

void Drive_motors(Motor_direction direction, uint32_t speed_percentage);

void Stop_motors();

#endif 

