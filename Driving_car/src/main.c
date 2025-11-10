#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include <stdint.h>
#include "pwm.h"
#include "motor_controls.h"

// static const struct gpio_dt_spec motor_a_in1 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in1), gpios);
// static const struct gpio_dt_spec motor_a_in2 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in2), gpios);
// static const struct gpio_dt_spec motor_a_in3 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in3), gpios);
// static const struct gpio_dt_spec motor_a_in4 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in4), gpios);

// static const struct gpio_dt_spec motor_b_in1 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in1), gpios);
// static const struct gpio_dt_spec motor_b_in2 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in2), gpios);
// static const struct gpio_dt_spec motor_b_in3 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in3), gpios);
// static const struct gpio_dt_spec motor_b_in4 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in4), gpios);


int main(void){
    /* --- 2. CHECK IF ALL DEVICES ARE READY --- */
    // if (!gpio_is_ready_dt(&motor_a_in1) || !gpio_is_ready_dt(&motor_a_in2) ||
    //     !gpio_is_ready_dt(&motor_b_in1) || !gpio_is_ready_dt(&motor_b_in2) || 
    //     !gpio_is_ready_dt(&motor_a_in3) || !gpio_is_ready_dt(&motor_a_in4) || 
    //     !gpio_is_ready_dt(&motor_b_in3) || !gpio_is_ready_dt(&motor_b_in4)) {
    //     printk("Error: One or more GPIO devices not ready.\n");
    //     return 0; // Pins not ready
    // }else {
    //     printk("All GPIO devices are ready.\n");
    // }

    // /* --- 3. CONFIGURE ALL 6 PINS AS OUTPUTS --- */
    // gpio_pin_configure_dt(&motor_a_in1, GPIO_OUTPUT_INACTIVE);
    // gpio_pin_configure_dt(&motor_a_in2, GPIO_OUTPUT_INACTIVE);
    // gpio_pin_configure_dt(&motor_a_in3, GPIO_OUTPUT_INACTIVE);
    // gpio_pin_configure_dt(&motor_a_in4, GPIO_OUTPUT_INACTIVE);

    // gpio_pin_configure_dt(&motor_b_in1, GPIO_OUTPUT_INACTIVE);
    // gpio_pin_configure_dt(&motor_b_in2, GPIO_OUTPUT_INACTIVE);
    // gpio_pin_configure_dt(&motor_b_in3, GPIO_OUTPUT_INACTIVE);
    // gpio_pin_configure_dt(&motor_b_in4, GPIO_OUTPUT_INACTIVE);
    
    pwm_begin();
    motors_start();
    // Drive_motors(Forward, 50);
    Drive_motors(Forward, 100);
    k_msleep(5000);

    // while (1) {
    //     // --- Motors forward at 100% speed ---
    //     gpio_pin_set_dt(&motor_a_in1, 1); // Motor A Forward (IN1=HIGH, IN2=LOW)
    //     gpio_pin_set_dt(&motor_a_in2, 0); 
    //     pwm_write_front_a(pwm_period_ns_half);
    //     printk("Motor A Front Speed set to 50%%\n");

    //     gpio_pin_set_dt(&motor_a_in3, 1);
    //     gpio_pin_set_dt(&motor_a_in4, 0);
    //     
    //     pwm_write_front_b(pwm_period_ns_half);
    //     printk("Motor A Back Speed set to 50%%\n");

    //     gpio_pin_set_dt(&motor_b_in1, 1); // Motor B Forward (IN3=HIGH, IN4=LOW)
    //     gpio_pin_set_dt(&motor_b_in2, 0);
    //     pwm_write_back_a(pwm_period_ns_half);
    //     printk("Motor B Front Speed set to 50%%\n");

    //     gpio_pin_set_dt(&motor_b_in3, 1);
    //     gpio_pin_set_dt(&motor_b_in4, 0);
    //     pwm_write_back_b(pwm_period_ns_half);
    //     printk("Motor B Back Speed set to 50%%\n");
    //     k_msleep(5000); // Run forward for 5 seconds
    //     k_msleep(3000); // Run forward for 3 seconds

    //     gpio_pin_set_dt(&motor_a_in1, 1); // Motor A Forward (IN1=HIGH, IN2=LOW)
    //     gpio_pin_set_dt(&motor_a_in2, 0); 
    //     pwm_write_front_a(pwm_period_ns_quarter);
    //     printk("Motor A Front Speed set to 25%%\n");

    //     gpio_pin_set_dt(&motor_a_in3, 1);
    //     gpio_pin_set_dt(&motor_a_in4, 0);
    //     pwm_write_front_b(pwm_period_ns_quarter);
    //     printk("Motor A Back Speed set to 25%%\n");

    //     gpio_pin_set_dt(&motor_b_in1, 1); // Motor B Forward (IN3=HIGH, IN4=LOW)
    //     gpio_pin_set_dt(&motor_b_in2, 0);
    //     pwm_write_back_a(pwm_period_ns_quarter);
    //     printk("Motor B Front Speed set to 25%%\n");

    //     gpio_pin_set_dt(&motor_b_in3, 1);
    //     gpio_pin_set_dt(&motor_b_in4, 0);
    //     pwm_write_back_b(pwm_period_ns_quarter);
    //     printk("Motor B Back Speed set to 25%%\n");

    //     k_msleep(3000); // Stop for 1 second

    //     gpio_pin_set_dt(&motor_a_in1, 1); // Motor A Forward (IN1=HIGH, IN2=LOW)
    //     gpio_pin_set_dt(&motor_a_in2, 0); 
    //     pwm_write_front_a(pwm_period_ns);
    //     printk("Motor A Front Speed set to 100%%\n");

    //     gpio_pin_set_dt(&motor_a_in3, 1);
    //     gpio_pin_set_dt(&motor_a_in4, 0);
    //     pwm_write_front_b(pwm_period_ns);
    //     printk("Motor A Back Speed set to 100%%\n");

    //     gpio_pin_set_dt(&motor_b_in1, 1); // Motor B Forward (IN3=HIGH, IN4=LOW)
    //     gpio_pin_set_dt(&motor_b_in2, 0);
    //     pwm_write_back_a(pwm_period_ns);
    //     printk("Motor B Front Speed set to 100%%\n");

    //     gpio_pin_set_dt(&motor_b_in3, 1);
    //     gpio_pin_set_dt(&motor_b_in4, 0);
    //     pwm_write_back_b(pwm_period_ns);
    //     printk("Motor B Back Speed set to 100%%\n");

    //     k_msleep(3000); // Stop for 1 second

    //     // --- Motors stop (coast) ---
    //     /* Turn off Enable pins */
    //     gpio_pin_set_dt(&motor_a_in1, 0); // Motor A Forward (IN1=HIGH, IN2=LOW)
    //     gpio_pin_set_dt(&motor_a_in2, 1);

    //     gpio_pin_set_dt(&motor_a_in3, 0);
    //     gpio_pin_set_dt(&motor_a_in4, 1);
        
    //     gpio_pin_set_dt(&motor_b_in1, 0); // Motor B Forward (IN3=HIGH, IN4=LOW)
    //     gpio_pin_set_dt(&motor_b_in2, 1);

    //     gpio_pin_set_dt(&motor_b_in3, 0);
    //     gpio_pin_set_dt(&motor_b_in4, 1);

    // }
    
    return 0;
}

