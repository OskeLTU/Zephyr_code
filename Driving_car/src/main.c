#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>


static const struct gpio_dt_spec motor_a_in1 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in1), gpios);
static const struct gpio_dt_spec motor_a_in2 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in2), gpios);
static const struct gpio_dt_spec motor_a_in3 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in3), gpios);
static const struct gpio_dt_spec motor_a_in4 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_a_in4), gpios);

static const struct gpio_dt_spec motor_b_in1 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in1), gpios);
static const struct gpio_dt_spec motor_b_in2 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in2), gpios);
static const struct gpio_dt_spec motor_b_in3 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in3), gpios);
static const struct gpio_dt_spec motor_b_in4 = GPIO_DT_SPEC_GET(DT_NODELABEL(motor_b_in4), gpios);

static const struct pwm_dt_spec motor_a_front_speed = PWM_DT_SPEC_GET(DT_NODELABEL(motor_a_front_speed));
static const struct pwm_dt_spec motor_b_front_speed = PWM_DT_SPEC_GET(DT_NODELABEL(motor_b_front_speed));
static const struct pwm_dt_spec motor_a_back_speed = PWM_DT_SPEC_GET(DT_NODELABEL(motor_a_back_speed));
static const struct pwm_dt_spec motor_b_back_speed = PWM_DT_SPEC_GET(DT_NODELABEL(motor_b_back_speed));




int main(void)
{
    /* --- 2. CHECK IF ALL DEVICES ARE READY --- */
    if (!gpio_is_ready_dt(&motor_a_in1) || !gpio_is_ready_dt(&motor_a_in2) ||
        !gpio_is_ready_dt(&motor_b_in1) || !gpio_is_ready_dt(&motor_b_in2) || 
        !gpio_is_ready_dt(&motor_a_in3) || !gpio_is_ready_dt(&motor_a_in4) || 
        !gpio_is_ready_dt(&motor_b_in3) || !gpio_is_ready_dt(&motor_b_in4)) {
        printk("Error: One or more GPIO devices not ready.\n");
        return 0; // Pins not ready
    }

    /* --- 3. CONFIGURE ALL 6 PINS AS OUTPUTS --- */
    gpio_pin_configure_dt(&motor_a_in1, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&motor_a_in2, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&motor_a_in3, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&motor_a_in4, GPIO_OUTPUT_INACTIVE);

    gpio_pin_configure_dt(&motor_b_in1, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&motor_b_in2, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&motor_b_in3, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&motor_b_in4, GPIO_OUTPUT_INACTIVE);

    uint32_t period_ns = 50000; // 20 kHz PWM frequency
    uint32_t duty_50 = period_ns / 2;
    uint32_t duty_25 = period_ns /4;

    /* --- 4. CONTROL LOOP --- */
    while (1) {
        // --- Motors forward at 100% speed ---
        gpio_pin_set_dt(&motor_a_in1, 1); // Motor A Forward (IN1=HIGH, IN2=LOW)
        gpio_pin_set_dt(&motor_a_in2, 0); 
        pwm_set_dt(&motor_a_front_speed, period_ns, duty_50);
        printk("Motor A Front Speed set to 50%%\n");

        gpio_pin_set_dt(&motor_a_in3, 1);
        gpio_pin_set_dt(&motor_a_in4, 0);
        pwm_set_dt(&motor_a_back_speed, period_ns, duty_50);
        printk("Motor A Back Speed set to 50%%\n");

        gpio_pin_set_dt(&motor_b_in1, 1); // Motor B Forward (IN3=HIGH, IN4=LOW)
        gpio_pin_set_dt(&motor_b_in2, 0);
        pwm_set_dt(&motor_b_front_speed, period_ns, duty_50);
        printk("Motor B Front Speed set to 50%%\n");

        gpio_pin_set_dt(&motor_b_in3, 1);
        gpio_pin_set_dt(&motor_b_in4, 0);
        pwm_set_dt(&motor_b_back_speed, period_ns, duty_50);
        printk("Motor B Back Speed set to 50%%\n");

        k_msleep(3000); // Run forward for 3 seconds

        gpio_pin_set_dt(&motor_a_in1, 1); // Motor A Forward (IN1=HIGH, IN2=LOW)
        gpio_pin_set_dt(&motor_a_in2, 0); 
        pwm_set_dt(&motor_a_front_speed, period_ns, duty_25);
        printk("Motor A Front Speed set to 25%%\n");

        gpio_pin_set_dt(&motor_a_in3, 1);
        gpio_pin_set_dt(&motor_a_in4, 0);
        pwm_set_dt(&motor_a_back_speed, period_ns, duty_25);
        printk("Motor A Back Speed set to 25%%\n");

        gpio_pin_set_dt(&motor_b_in1, 1); // Motor B Forward (IN3=HIGH, IN4=LOW)
        gpio_pin_set_dt(&motor_b_in2, 0);
        pwm_set_dt(&motor_b_front_speed, period_ns, duty_25);
        printk("Motor B Front Speed set to 25%%\n");

        gpio_pin_set_dt(&motor_b_in3, 1);
        gpio_pin_set_dt(&motor_b_in4, 0);
        pwm_set_dt(&motor_b_back_speed, period_ns, duty_25);
        printk("Motor B Back Speed set to 25%%\n");

        k_msleep(3000); // Stop for 1 second

        gpio_pin_set_dt(&motor_a_in1, 1); // Motor A Forward (IN1=HIGH, IN2=LOW)
        gpio_pin_set_dt(&motor_a_in2, 0); 
        pwm_set_dt(&motor_a_front_speed, period_ns, period_ns);
        printk("Motor A Front Speed set to 100%%\n");

        gpio_pin_set_dt(&motor_a_in3, 1);
        gpio_pin_set_dt(&motor_a_in4, 0);
        pwm_set_dt(&motor_a_back_speed, period_ns, period_ns);
        printk("Motor A Back Speed set to 100%%\n");

        gpio_pin_set_dt(&motor_b_in1, 1); // Motor B Forward (IN3=HIGH, IN4=LOW)
        gpio_pin_set_dt(&motor_b_in2, 0);
        pwm_set_dt(&motor_b_front_speed, period_ns, period_ns);
        printk("Motor B Front Speed set to 25%%\n");

        gpio_pin_set_dt(&motor_b_in3, 1);
        gpio_pin_set_dt(&motor_b_in4, 0);
        pwm_set_dt(&motor_b_back_speed, period_ns, period_ns);
        printk("Motor B Back Speed set to 100%%\n");

        k_msleep(3000); // Stop for 1 second

        // // --- Motors stop (coast) ---
        // /* Turn off Enable pins */
        // gpio_pin_set_dt(&motor_a_in1, 0); // Motor A Forward (IN1=HIGH, IN2=LOW)
        // gpio_pin_set_dt(&motor_a_in2, 1);

        // gpio_pin_set_dt(&motor_a_in3, 0);
        // gpio_pin_set_dt(&motor_a_in4, 1);
        
        // gpio_pin_set_dt(&motor_b_in1, 0); // Motor B Forward (IN3=HIGH, IN4=LOW)
        // gpio_pin_set_dt(&motor_b_in2, 1);

        // gpio_pin_set_dt(&motor_b_in3, 0);
        // gpio_pin_set_dt(&motor_b_in4, 1);

        
    }
    return 0;
}