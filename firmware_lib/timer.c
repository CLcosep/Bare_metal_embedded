#include "timer.h"

#define RCC_APB1ENR (*(volatile uint32_t *)0x4002101C)
#define TIM2_CR1    (*(volatile uint32_t *)0x40000000)
#define TIM2_CCMR1  (*(volatile uint32_t *)0x40000018)
#define TIM2_CCER   (*(volatile uint32_t *)0x40000020)
#define TIM2_PSC    (*(volatile uint32_t *)0x40000028)
#define TIM2_ARR    (*(volatile uint32_t *)0x4000002C)
#define TIM2_CCR1   (*(volatile uint32_t *)0x40000034)

void tim2_pwm_init(uint16_t psc, uint16_t arr) {
    RCC_APB1ENR |= (1 << 0);
    TIM2_PSC = psc;    
    TIM2_ARR = arr;
    TIM2_CCMR1 |= (1 << 6) | (1 << 5);  
    TIM2_CCER |= (1 << 0);   
    TIM2_CR1 |= (1 << 0);
}

void tim2_pwm_set_delay(uint16_t duty){
    TIM2_CCR1 = duty;
}