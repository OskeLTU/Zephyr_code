#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "gatekeeper.h"
#include "motor_controls.h"

static bool bt_active = false;
static int64_t bt_timer_until_timeout = 0;

#define CONTROL_TIMEOUT_MS 30

void bluetouth_signal_recived(){
    bt_timer_until_timeout = k_uptime_get();
    if(!bt_active){
        printk("Bluetooth control activated.\n");
        bt_active = true;
        
    }
}

void timeout_control(){
    if(bt_active){
        int64_t current_time = k_uptime_get();
        if(current_time - bt_timer_until_timeout >= CONTROL_TIMEOUT_MS){
            bt_active = false;
            printk("Bluetooth control deactivated due to timeout.\n");
            execute_serial_last_action();
        }
    }
}

bool bluetouth_in_control(){
    return bt_active;
}