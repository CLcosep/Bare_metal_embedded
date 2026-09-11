#include <stdint.h>
#include "../firmware_lib/gpio.h"


int main(void) {
    // RCC_APB2ENR |= (1 << 2) | (1 << 4); //turn GPIOA clock (IOPAEN, 2 bits), turn on GPIOC clock
// 
    // PA0 input, pullup
    // GPIOA_CRL &= ~(0xF << 0); //clear 4 bits for pin0
    // GPIOA_CRL |= (0x2 << 2);  //MODE0 = 00 (input) CNF1 = 10 (input with pull-up/pull-down)
    // GPIOA_ODR |= (1 << 0); //select pull-up for PA0
// 
    // PC13: output, push-pull
    // GPIOC_CRH &= ~(0xF << 20);
    // GPIOC_CRH |= (0x1 << 20);
// 
    // while (1) {
        // if ((GPIOA_IDR & (1 << 0)) == 0) {
            // GPIOC_ODR &= ~(1 << 13); //btn pressed -> drive pin 13 low
        // } else {
            // GPIOC_ODR |= (1 << 13); //btn released -> drive PC13 high
        // }
    // }

    gpio_clock_en(GPIOA_BASE);
    gpio_clock_en(GPIOC_BASE);

    gpio_set_mode(GPIOA_BASE, 0, GPIO_CNF_INPUT_PP);
    gpio_write(GPIOA_BASE, 0, 1);

    gpio_set_mode(GPIOC_BASE, 13, GPIO_CNF_OUTPUT_PP_10MHZ);

    while(1) {
        if (gpio_read(GPIOA_BASE, 0) == 0) {
            gpio_write(GPIOA_BASE, 13, 0);
        } else {
            gpio_write(GPIOC_BASE, 13, 1);
        }
    }
}