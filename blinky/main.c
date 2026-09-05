#include <stdint.h>

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018)
#define GPIOC_CRH   (*(volatile uint32_t *)0x40011004)
#define GPIOC_ODR   (*(volatile uint32_t *)0x4001100C)
// adding Timers
#define RCC_APB1ENR (*(volatile uint32_t *)0x4002101C)
#define TIM2_CR1    (*(volatile uint32_t *)0x40000000)
#define TIM2_SR     (*(volatile uint32_t *)0x40000010)
#define TIM2_EGR    (*(volatile uint32_t *)0x40000014)
#define TIM2_CNT    (*(volatile uint32_t *)0x40000024)
#define TIM2_PSC    (*(volatile uint32_t *)0x40000028)
#define TIM2_ARR    (*(volatile uint32_t *)0x4000002C)
// SysTick
#define SYST_CSR    (*(volatile uint32_t *)0xE000E010)
#define SYST_RVR    (*(volatile uint32_t *)0xE000E014)
#define SYST_CVR    (*(volatile uint32_t *)0xE000E018)

volatile uint32_t ms_tick = 0;

void SysTick_Handler(void) {
    ms_tick++;
}

// void delay_ms(uint32_t ms) {
//     TIM2_PSC = 7999;    //8MHz / 8000 = 1kHz -> 1ms per tick
//     TIM2_ARR = ms - 1;
//     TIM2_EGR |= (1 << 0);   //UG bit: force-apply PSC/ARR immediately, reset CNT to 0
//     TIM2_SR &= ~(1 << 0);   //clear any stale UIF flag before starting
//     TIM2_CR1 |= (1 << 0);   //CEN bit: start coutning 

//     while (!(TIM2_SR & (1 << 0))); // wait for UIF

//     TIM2_CR1 &= ~(1 << 0); //stop the timer
// }

int main(void) {
    RCC_APB2ENR |= (1 << 4); //turn GPIOC clock (IOPCEN)
    // timer TIM2
    // RCC_APB1ENR |= (1 << 0); //bit 0 TIM2EN

    GPIOC_CRH &= ~(0xF << 20); //clear 4 bits for pin13
    GPIOC_CRH |= (0x1 << 20);  //MODE13 = 01 (Output, 10MHZ) CNF13 = 00 (push pull)

    SYST_RVR = 7999;
    SYST_CVR = 0;
    SYST_CSR = (1 << 0) | (1 << 1) | (1 << 2);

    uint32_t last_toggle = 0;

    // while (1) {
    //     GPIOC_ODR ^= (1 << 13); //toggle pc13
    //     // for (volatile int i = 0; i < 200000; i++); //crude delay
    //     delay_ms(500);
    // }

    while (1) {
        if ((ms_tick - last_toggle) >= 500) {
            GPIOC_ODR ^= (1 << 13);
            last_toggle = ms_tick;
        }
    }
}