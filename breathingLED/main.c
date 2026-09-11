#include <stdint.h>
#include "../firmware_lib/gpio.h"
#include "../firmware_lib/timer.h"

int main(void) {

    // RCC_APB2ENR |= (1 << 0) | (1 << 2); //AFIOEN, IOPAEN
    // RCC_APB1ENR |= (1 << 0);            //TIM2EN

    // GPIOA_CRL &= ~(0xF << 0); //clear pin0 4 bits
    // GPIOA_CRL |= (0xB << 0);    // write 1011 

    // TIM2_PSC = 7;       //8mHz / 8 = 1 MHz timer clock
    // TIM2_ARR = 999;     // 1MHz / 1000 = 1kHz PWM freq

    // TIM2_CCMR1 |= (1 << 6) | (1 << 5);      // PWM mode 1
    // TIM2_CCER  |= (1 << 0);         //enable channel 1 output
    // TIM2_CR1 |= (1 << 0);       //start timer

    // while(1) {
    //     for (int duty = 0; duty <= 999; duty++){
    //         TIM2_CCR1 = duty;
    //         for(volatile int i = 0; i < 500; i++);  //small pace setting delay
    //     }
    //     for(int duty = 999; duty >= 0; duty--){
    //         TIM2_CCR1 = duty;
    //         for(volatile int i = 0; i < 500; i++);
    //     }
    // }

    gpio_afio_en();
    gpio_clock_en(GPIOA_BASE);
    gpio_set_mode(GPIOA_BASE, 0, GPIO_CNF_AF_OUTPUT_PP_50MHZ);
    tim2_pwm_init(7, 999);

    while(1) {
        for (int duty = 0; duty <= 999; duty++){
            tim2_pwm_set_delay(duty);
            for(volatile int i = 0; i < 500; i++);  //small pace setting delay
        }
        for(int duty = 999; duty >= 0; duty--){
            tim2_pwm_set_delay(duty);
            for(volatile int i = 0; i < 500; i++);
        }
    }


}