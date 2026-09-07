#include <stdint.h>

#define RCC_APB2ENR (*(volatile uint32_t *) 0x40021018)
#define RCC_APB1ENR (*(volatile uint32_t *) 0x4002101C)
#define GPIOA_CRL   (*(volatile uint32_t *) 0x40010800)
#define TIM2_CR1    (*(volatile uint32_t *) 0x40000000)
#define TIM2_CCMR1  (*(volatile uint32_t *) 0x40000018)
#define TIM2_CCER   (*(volatile uint32_t *) 0x40000020)
#define TIM2_PSC    (*(volatile uint32_t *) 0x40000028)
#define TIM2_ARR    (*(volatile uint32_t *) 0x4000002C)
#define TIM2_CCR1   (*(volatile uint32_t *) 0x40000034)

int main(void) {

    RCC_APB2ENR |= (1 << 0) | (1 << 2); //AFIOEN, IOPAEN
    RCC_APB1ENR |= (1 << 0);            //TIM2EN

    GPIOA_CRL &= ~(0xF << 0); //clear pin0 4 bits
    GPIOA_CRL |= (0xB << 0);    // write 1011 

    TIM2_PSC = 7;       //8mHz / 8 = 1 MHz timer clock
    TIM2_ARR = 999;     // 1MHz / 1000 = 1kHz PWM freq

    TIM2_CCMR1 |= (1 << 6) | (1 << 5);      // PWM mode 1
    TIM2_CCER  |= (1 << 0);         //enable channel 1 output
    TIM2_CR1 |= (1 << 0);       //start timer

    while(1) {
        for (int duty = 0; duty <= 999; duty++){
            TIM2_CCR1 = duty;
            for(volatile int i = 0; i < 500; i++);  //small pace setting delay
        }
        for(int duty = 999; duty >= 0; duty--){
            TIM2_CCR1 = duty;
            for(volatile int i = 0; i < 500; i++);
        }
    }


}