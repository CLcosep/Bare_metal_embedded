#include "gpio.h"

#define RCC_APB2ENR (*(volatile uint32_t *) 0x40021018)

static volatile uint32_t* crl(uint32_t base){return (volatile uint32_t *) (base + 0x00); }
static volatile uint32_t* crh(uint32_t base){return (volatile uint32_t *) (base + 0x04); }
static volatile uint32_t* idr(uint32_t base){return (volatile uint32_t *) (base + 0x08); }
static volatile uint32_t* odr(uint32_t base){return (volatile uint32_t *) (base + 0x0C); }


void gpio_afio_en(void) {
    RCC_APB2ENR |= (1 << 0);
}

void gpio_clock_en(uint32_t port_base) {
    // enable IOPAEN, IOPBEN, IOPCEN
    if (port_base == GPIOA_BASE) RCC_APB2ENR |= (1 << 2);
    else if (port_base == GPIOB_BASE) RCC_APB2ENR |= (1 << 3);
    else if (port_base == GPIOC_BASE) RCC_APB2ENR |= (1 << 4);
}

void gpio_set_mode(uint32_t port_base, uint8_t pin, uint8_t cnf_mode) {
    // set crl or crh
    volatile uint32_t *reg = (pin < 8) ? crl(port_base) : crh(port_base);
    uint8_t shift = (pin % 8) * 4;
    *reg &= ~(0xFUL << shift);                  //clear
    *reg |= ((uint32_t)cnf_mode << shift);      //set
}

void gpio_write(uint32_t port_base, uint8_t pin, uint8_t state) {
    if (state) *odr(port_base) |= (1 << pin);
    else *odr(port_base) &= ~(1 << pin);
}

void gpio_toggle(uint32_t port_base, uint8_t pin) {
    *odr(port_base) ^= (1 << pin);
}

uint8_t gpio_read(uint32_t port_base, uint8_t pin) {
    return (*idr(port_base) >> pin) & 0x1;
}

void gpio_pullup_en(uint32_t port_base, uint8_t pin) {
    gpio_write(port_base, pin, 1);
}