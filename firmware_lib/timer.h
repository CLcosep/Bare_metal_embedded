#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>

void tim2_pwm_init(uint16_t psc, uint16_t arr);
void tim2_pwm_set_delay(uint16_t duty);


#endif