#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>

#include "pwm.h"

static const struct gpio_dt_spec motor_a_in1 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in1), gpios);
static const struct gpio_dt_spec motor_a_in2 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in2), gpios);
static const struct gpio_dt_spec motor_a_in3 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in3), gpios);
static const struct gpio_dt_spec motor_a_in4 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in4), gpios);

static const struct gpio_dt_spec motor_b_in1 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in1), gpios);
static const struct gpio_dt_spec motor_b_in2 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in2), gpios);
static const struct gpio_dt_spec motor_b_in3 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in3), gpios);
static const struct gpio_dt_spec motor_b_in4 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in4), gpios);

// static const struct device *front_speed_a;
// static const struct device *back_speed_a;
// static const struct device *front_speed_b;
// static const struct device *back_speed_b;


// int pwm_write(const struct device *dev, uint32_t value){
//     return pwm_set(dev, 0, 1000000, value, 0);
// }

// int main(void){
//     /* --- 2. CHECK IF ALL DEVICES ARE READY --- */
//     if (!gpio_is_ready_dt(&motor_a_in1) || !gpio_is_ready_dt(&motor_a_in2) ||
//         !gpio_is_ready_dt(&motor_b_in1) || !gpio_is_ready_dt(&motor_b_in2) || 
//         !gpio_is_ready_dt(&motor_a_in3) || !gpio_is_ready_dt(&motor_a_in4) || 
//         !gpio_is_ready_dt(&motor_b_in3) || !gpio_is_ready_dt(&motor_b_in4)) {
//         printk("Error: One or more GPIO devices not ready.\n");
//         return 0; // Pins not ready
//     }else {
//         printk("All GPIO devices are ready.\n");
//     }

//     /* --- 3. CONFIGURE ALL 6 PINS AS OUTPUTS --- */
//     gpio_pin_configure_dt(&motor_a_in1, GPIO_OUTPUT_INACTIVE);
//     gpio_pin_configure_dt(&motor_a_in2, GPIO_OUTPUT_INACTIVE);
//     gpio_pin_configure_dt(&motor_a_in3, GPIO_OUTPUT_INACTIVE);
//     gpio_pin_configure_dt(&motor_a_in4, GPIO_OUTPUT_INACTIVE);

//     gpio_pin_configure_dt(&motor_b_in1, GPIO_OUTPUT_INACTIVE);
//     gpio_pin_configure_dt(&motor_b_in2, GPIO_OUTPUT_INACTIVE);
//     gpio_pin_configure_dt(&motor_b_in3, GPIO_OUTPUT_INACTIVE);
//     gpio_pin_configure_dt(&motor_b_in4, GPIO_OUTPUT_INACTIVE);

//     // if ((front_speed_a = device_get_binding("PWM_0")) == NULL ||
//     //     (front_speed_b = device_get_binding("PWM_1")) == NULL ||
//     //     (back_speed_a = device_get_binding("PWM_2")) == NULL ||
//     //     (back_speed_b = device_get_binding("PWM_3")) == NULL) {
//     //     printk("Error: One or more PWM devices not found.\n");
//     //     return 0; // PWM devices not found
//     // }else{
//     //     printk("All PWM devices are ready.\n");
//     // }
//     int ret;
//     ret = pwm_begin();

//     // uint32_t period_ns = 1000000000; // 1 kHz PWM frequency
//     // uint32_t pulse_ns = period_ns/2;;

//     /* --- 4. CONTROL LOOP --- */
//     while (1) {
//         // --- Motors forward at 100% speed ---
//         gpio_pin_set_dt(&motor_a_in1, 1); // Motor A Forward (IN1=HIGH, IN2=LOW)
//         gpio_pin_set_dt(&motor_a_in2, 0); 
//         // pwm_write(front_speed_a, 500000000);
//         pwm_write((2048* pwm_period_ns)/4096);
//         printk("Motor A Front Speed set to 50%%\n");

//         gpio_pin_set_dt(&motor_a_in3, 1);
//         gpio_pin_set_dt(&motor_a_in4, 0);
//         // pwm_write(back_speed_a, 500000000);
//         pwm_write((2048* pwm_period_ns)/4096);
//         printk("Motor A Back Speed set to 50%%\n");

//         gpio_pin_set_dt(&motor_b_in1, 1); // Motor B Forward (IN3=HIGH, IN4=LOW)
//         gpio_pin_set_dt(&motor_b_in2, 0);
//         pwm_write((2048* pwm_period_ns)/4096);
//         printk("Motor B Front Speed set to 50%%\n");

//         gpio_pin_set_dt(&motor_b_in3, 1);
//         gpio_pin_set_dt(&motor_b_in4, 0);
//         pwm_write((2048* pwm_period_ns)/4096);
//         printk("Motor B Back Speed set to 50%%\n");
//         k_msleep(5000); // Run forward for 5 seconds
//     //     k_msleep(3000); // Run forward for 3 seconds

//     //     gpio_pin_set_dt(&motor_a_in1, 1); // Motor A Forward (IN1=HIGH, IN2=LOW)
//     //     gpio_pin_set_dt(&motor_a_in2, 0); 
//     //     pwm_write(front_speed_a, period_ns/4);
//     //     printk("Motor A Front Speed set to 25%%\n");

//     //     gpio_pin_set_dt(&motor_a_in3, 1);
//     //     gpio_pin_set_dt(&motor_a_in4, 0);
//     //     pwm_write(back_speed_a, period_ns/4);
//     //     printk("Motor A Back Speed set to 25%%\n");

//     //     gpio_pin_set_dt(&motor_b_in1, 1); // Motor B Forward (IN3=HIGH, IN4=LOW)
//     //     gpio_pin_set_dt(&motor_b_in2, 0);
//     //     pwm_write(front_speed_b, period_ns/4);
//     //     printk("Motor B Front Speed set to 25%%\n");

//     //     gpio_pin_set_dt(&motor_b_in3, 1);
//     //     gpio_pin_set_dt(&motor_b_in4, 0);
//     //     pwm_write(back_speed_b, period_ns/4);
//     //     printk("Motor B Back Speed set to 25%%\n");

//     //     k_msleep(3000); // Stop for 1 second

//     //     gpio_pin_set_dt(&motor_a_in1, 1); // Motor A Forward (IN1=HIGH, IN2=LOW)
//     //     gpio_pin_set_dt(&motor_a_in2, 0); 
//     //     pwm_write(front_speed_a, period_ns);
//     //     printk("Motor A Front Speed set to 100%%\n");

//     //     gpio_pin_set_dt(&motor_a_in3, 1);
//     //     gpio_pin_set_dt(&motor_a_in4, 0);
//     //     pwm_write(back_speed_a, period_ns);
//     //     printk("Motor A Back Speed set to 100%%\n");

//     //     gpio_pin_set_dt(&motor_b_in1, 1); // Motor B Forward (IN3=HIGH, IN4=LOW)
//     //     gpio_pin_set_dt(&motor_b_in2, 0);
//     //     pwm_write(front_speed_b, period_ns);
//     //     printk("Motor B Front Speed set to 100%%\n");

//     //     gpio_pin_set_dt(&motor_b_in3, 1);
//     //     gpio_pin_set_dt(&motor_b_in4, 0);
//     //     pwm_write(back_speed_b, period_ns);
//     //     printk("Motor B Back Speed set to 100%%\n");

//     //     k_msleep(3000); // Stop for 1 second

//     //     // --- Motors stop (coast) ---
//     //     /* Turn off Enable pins */
//     //     gpio_pin_set_dt(&motor_a_in1, 0); // Motor A Forward (IN1=HIGH, IN2=LOW)
//     //     gpio_pin_set_dt(&motor_a_in2, 1);

//     //     gpio_pin_set_dt(&motor_a_in3, 0);
//     //     gpio_pin_set_dt(&motor_a_in4, 1);
        
//     //     gpio_pin_set_dt(&motor_b_in1, 0); // Motor B Forward (IN3=HIGH, IN4=LOW)
//     //     gpio_pin_set_dt(&motor_b_in2, 1);

//     //     gpio_pin_set_dt(&motor_b_in3, 0);
//     //     gpio_pin_set_dt(&motor_b_in4, 1);

        
//     }
//     return 0;
// }

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/pwm.h>
#include "pwm.h"

int main(void)
{
    int ret = pwm_begin();
    if (ret != 0) {
        printk("PWM init failed\n");
        return -1;
    }

    // Set LED to 50% duty cycle continuously
    pwm_write(pwm_period_ns / 2);

    // Now just loop doing nothing — PWM runs in hardware
    while (1) {
        // Nothing here, PWM is independent of CPU
    }

    return 0;
}
