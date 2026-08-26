#include <stdint.h>

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018)
#define GPIOA_CRL   (*(volatile uint32_t *)0x40010800)
#define GPIOA_IDR   (*(volatile uint32_t *)0x40010808)
#define GPIOA_ODR   (*(volatile uint32_t *)0x4001080C)
#define GPIOC_CRH   (*(volatile uint32_t *)0x40011004)
#define GPIOC_ODR   (*(volatile uint32_t *)0x4001100C)

int main(void) {
    RCC_APB2ENR |= (1 << 2) | (1 << 4); //turn GPIOA clock (IOPAEN, 2 bits), turn on GPIOC clock

    // PA0 input, pullup
    GPIOA_CRL &= ~(0xF << 0); //clear 4 bits for pin0
    GPIOA_CRL |= (0x2 << 2);  //MODE0 = 00 (input) CNF1 = 10 (input with pull-up/pull-down)
    GPIOA_ODR |= (1 << 0); //select pull-up for PA0

    // PC13: output, push-pull
    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |= (0x1 << 20);

    while (1) {
        if ((GPIOA_IDR & (1 << 0)) == 0) {
            GPIOC_ODR &= ~(1 << 13); //btn pressed -> drive pin 13 low
        } else {
            GPIOC_ODR |= (1 << 13); //btn released -> drive PC13 high
        }
    }
}