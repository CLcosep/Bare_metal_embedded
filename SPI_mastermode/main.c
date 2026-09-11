#include <stdint.h>
#include "../firmware_lib/gpio.h"
#include "../firmware_lib/spi.h"


// uint8_t spi_transfer(uint8_t byte) {
//     while(!(SPI1_SR & (1 << 1)));
//     SPI1_DR = byte;
//     while(!(SPI1_SR & (1 << 0)));
//     return SPI1_DR;
// }


int main(void) {

    // RCC_APB2ENR |= (1 << 0) | (1 << 2) | (1 << 12); //AFIOEN, IOPAEN, SPI1EN

    // GPIOA_CRL &= ~(0xFUL << 16); GPIOA_CRL |= (0x3UL << 16);    //PA4: NSS plain output
    // GPIOA_CRL &= ~(0xFUL << 20); GPIOA_CRL |= (0xBUL << 20);    //PA5: SCK
    // GPIOA_CRL &= ~(0xFUL << 24); GPIOA_CRL |= (0x4UL << 24);    //PA6: MISO
    // GPIOA_CRL &= ~(0xFUL << 28); GPIOA_CRL |= (0xBUL << 28);    //PA7: MOSI

    // GPIOA_ODR |= (1 << 4);  //NSS idle high(selected) - active low chip select

    // SPI1_CR1 |= (1 << 2);
    // SPI1_CR1 |= (3 << 3);
    // SPI1_CR1 |= (1 << 8) | (1 << 9);
    // SPI1_CR1 |= (1 << 6);
 
    // while(1) {
    //     GPIOA_ODR &= ~(1 << 4);     //select the slave (pull NSS low)
    //     uint8_t response  = spi_transfer(0xAA); //send test byte , capture whatever comes back
    //     GPIOA_ODR |= (1 << 4);  //deselct

    //     for (volatile int i = 0; i < 5000000; i++); //crude delay
    // }
    gpio_afio_en();
    gpio_clock_en(GPIOA_BASE);
    gpio_set_mode(GPIOA_BASE, 4, GPIO_CNF_OUTPUT_PP_50MHZ);     //NSS
    gpio_set_mode(GPIOA_BASE, 5, GPIO_CNF_AF_OUTPUT_PP_50MHZ);  //SCK
    gpio_set_mode(GPIOA_BASE, 6, GPIO_CNF_INPUT_FLOAT);         //MISO
    gpio_set_mode(GPIOA_BASE, 7, GPIO_CNF_AF_OUTPUT_PP_50MHZ);  //MOSI

    spi1_init();
    
    gpio_write(GPIOA_BASE, 4, 1);

    while(1) {
        gpio_write(GPIOA_BASE, 4, 0);
        uint8_t response = spi1_transfer(0xAA);
        gpio_write(GPIOA_BASE, 4, 1);

        for (volatile int i = 0; i < 500000; i++);
    }
}
