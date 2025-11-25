#ifndef MOTOR_CONTROLS_H
#define MOTOR_CONTROLS_H

typedef enum {
    Forward,
    Backward,
    Rotate_Right,
    Rotate_Left,
    Right,
    Left,
    Stop
}Motor_direction;

typedef enum{
    Motor_Left_Front,
    Motor_Left_Back,
    Motor_Right_Front,
    Motor_Right_Back
}Motor_name;

int motors_start();

void Drive_one_motor(Motor_name motor, Motor_direction direction, uint32_t speed_percentage);

void Drive_motors(Motor_direction direction, uint32_t speed_percentage);

void Stop_motors();

#endif 

