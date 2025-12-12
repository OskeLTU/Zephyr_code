
// This File has been writen by Wang King Son
// link to his github: https://github.com/WangKKing3
// Note: This file does use the motor_controls, pwm, and gatekeeper libraries that were written by Oskaras Dauneckas(ME)

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "car_control.h"
#include "receiver_ble.h"
#include "motor_controls.h"
#include "gatekeeper.h"


#define TIMEOUT_MS 1000      /* Stopp motorene hvis ingen data på 1 sekund */

static Motor_direction current_dir = Stop;
static uint8_t current_speed = 0;
static int64_t last_rx = 0;
static bool motors_on = false;

static const char *dir_name(Motor_direction d)
{
    switch (d) {
        case Forward: return "FWD";
        case Backward: return "BWD";
        case Rotate_Right: return "ROT_R";
        case Rotate_Left: return "ROT_L";
        case Right: return "RIGHT";
        case Left: return "LEFT";
        case Stop: return "STOP";
        case Idle: return "IDLE";
        default: return "?";
    }
}

static void on_drive_data(Motor_direction dir, uint8_t speed)
{
    last_rx = k_uptime_get();

    

    if(dir == Idle){
        // printk("Ignoring IDLE command.\n");
        // Stop_motors();
        motors_on = false;
        return;
    }

    bluetouth_signal_recived();

    printk("[RX] %-5s %3d%%\n", dir_name(dir), speed);

    if(dir == Stop){
        if (motors_on) {
            Stop_motors();
            motors_on = false;
        }
    } else {
        Drive_motors(dir, speed);
        motors_on = true;
    }
}

int car_controller_init(void)
{
    printk("\n=== BLE Car Receiver ===\n");
    printk("Receives Motor_direction directly\n\n");

    /* Init motors */
    if (motors_start() != 0) {
        printk("Motor init failed\n");
        return -1;
    }
    printk("Motors ready\n");

    /* Init BLE */
    if (ble_init(on_drive_data) != 0) {
        printk("BLE init failed\n");
        return -1;
    }
    printk("BLE initialized\n");
    return 0;

}

void car_controller_start(void){
    ble_start_scan();
}

void car_controller_check_timeout(void){ 
    /* Main loop - bare timeout sjekk */
    if (last_rx > 0 && motors_on) {
        int64_t age = k_uptime_get() - last_rx;
        if (age > TIMEOUT_MS) {
            printk("[TIMEOUT] Stopping\n");
            Stop_motors();
            motors_on = false;
            
        }
    }
}