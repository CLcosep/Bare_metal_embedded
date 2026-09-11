#include "spi.h"

#define RCC_APB2ENR     (*(volatile uint32_t *)0x40021018)
#define SPI1_CR1        (*(volatile uint32_t *)0x40013000)
#define SPI1_SR         (*(volatile uint32_t *)0x40013008)
#define SPI1_DR         (*(volatile uint32_t *)0x4001300C)

void spi1_init(void) {
    RCC_APB2ENR |= (1 << 12);
    SPI1_CR1 |= (1 << 2);
    SPI1_CR1 |= (3 << 3);
    SPI1_CR1 |= (1 << 8) | (1 << 9);
    SPI1_CR1 |= (1 << 6);
}

uint8_t spi1_transfer(uint8_t byte) {
    while(!(SPI1_SR & (1 << 1)));
    SPI1_DR = byte;
    while(!(SPI1_SR & (1 << 0)));
    return SPI1_DR;
}