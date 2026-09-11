#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>

// GPIO port base registers
#define GPIOA_BASE 0x40010800
#define GPIOB_BASE 0x40010C00
#define GPIOC_BASE 0x40011000

// GPIO port configurations
#define GPIO_CNF_OUTPUT_PP_10MHZ        0x1     //General purpose outut push-pull, max output speed 10MHZ
#define GPIO_CNF_OUTPUT_PP_50MHZ        0x3     //General purpose output push-pull, max output speed 50MHZ
#define GPIO_CNF_INPUT_FLOAT            0x4     //Input mode, floating input
#define GPIO_CNF_INPUT_PP               0x8     //Input mode, Input with pull-up/pull-down
#define GPIO_CNF_AF_OUTPUT_PP_50MHZ     0xB     //Alternate function output push-pull, max output speed 50MHZ

void gpio_afio_en(void);
void gpio_clock_en(uint32_t port_base);
void gpio_set_mode(uint32_t port_base, uint8_t pin, uint8_t cnf_mode);
void gpio_write(uint32_t port_base, uint8_t pin, uint8_t state);
void gpio_toggle(uint32_t port_base, uint8_t pin);
uint8_t gpio_read(uint32_t port_base, uint8_t pin);
void gpio_pullup_en(uint32_t port_base, uint8_t pin);

#endif