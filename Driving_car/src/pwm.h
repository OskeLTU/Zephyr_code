#ifndef __PWM_H
#define __PWM_H


#define pwm_period_ns 100000000 // 100 Hz PWM frequency
#define pwm_period_ns_half (pwm_period_ns / 2) // 50% duty cycle
#define pwm_period_ns_quarter (pwm_period_ns / 4) // 25% duty cycle

int pwm_begin();
int pwm_write(uint32_t value);
#endif /* __PWM_H */