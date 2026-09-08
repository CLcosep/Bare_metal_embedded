#include <stdint.h>

#define RCC_APB2ENR     (*(volatile uint32_t *)0x40021018)
#define GPIOA_CRL       (*(volatile uint32_t *)0x40010800)
#define GPIOA_ODR       (*(volatile uint32_t *)0x4001080C)
#define SPI1_CR1        (*(volatile uint32_t *)0x40013000)
#define SPI1_SR         (*(volatile uint32_t *)0x40013008)
#define SPI1_DR         (*(volatile uint32_t *)0x4001300C)


uint8_t spi_transfer(uint8_t byte) {
    while(!(SPI1_SR & (1 << 1)));
    SPI1_DR = byte;
    while(!(SPI1_SR & (1 << 0)));
    return SPI1_DR;
}

int main(void) {

    RCC_APB2ENR |= (1 << 0) | (1 << 2) | (1 << 12); //AFIOEN, IOPAEN, SPI1EN

    GPIOA_CRL &= ~(0xFUL << 16); GPIOA_CRL |= (0x3UL << 16);    //PA4: NSS plain output
    GPIOA_CRL &= ~(0xFUL << 20); GPIOA_CRL |= (0xBUL << 20);    //PA5: SCK
    GPIOA_CRL &= ~(0xFUL << 24); GPIOA_CRL |= (0x4UL << 24);    //PA6: MISO
    GPIOA_CRL &= ~(0xFUL << 28); GPIOA_CRL |= (0xBUL << 28);    //PA7: MOSI

    GPIOA_ODR |= (1 << 4);  //NSS idle high(selected) - active low chip select

    SPI1_CR1 |= (1 << 2);
    SPI1_CR1 |= (3 << 3);
    SPI1_CR1 |= (1 << 8) | (1 << 9);
    SPI1_CR1 |= (1 << 6);
 
    while(1) {
        GPIOA_ODR &= ~(1 << 4);     //select the slave (pull NSS low)
        uint8_t response  = spi_transfer(0xAA); //send test byte , capture whatever comes back
        GPIOA_ODR |= (1 << 4);  //deselct

        for (volatile int i = 0; i < 5000000; i++); //crude delay
    }
}
