#ifndef __PWM_H
#define __PWM_H

#define pwm_period_ns 100000000 // 100 Hz PWM frequency
int pwm_begin();
int pwm_write(uint32_t value);
#endif /* __PWM_H */