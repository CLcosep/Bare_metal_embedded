#include <stdint.h>

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018)
#define GPIOC_CRH   (*(volatile uint32_t *)0x40011004)
#define GPIOC_ODR   (*(volatile uint32_t *)0x4001100C)

int main(void) {
    RCC_APB2ENR |= (1 << 4); //turn GPIOC clock (IOPCEN)

    GPIOC_CRH &= ~(0xF << 20); //clear 4 bits for pin13
    GPIOC_CRH |= (0x1 <<20);  //MODE13 = 01 (Output, 10MHZ) CNF13 = 00 (push pull)

    while (1) {
        GPIOC_ODR ^= (1 << 13); //toggle pc13
        for (volatile int i = 0; i < 200000; i++); //crude delay
    }
}