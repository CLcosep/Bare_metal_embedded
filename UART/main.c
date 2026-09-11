#include <stdint.h>
#include "../firmware_lib/gpio.h"
#include "../firmware_lib/uart.h"

// void uart_send_byte(uint8_t byte);
// void uart_send_string(const char *s);
// uint8_t uart_read_byte(void);

int main(void) {
    // RCC_APB2ENR |= (1 << 0) | (1 << 2) | (1 << 4) | (1 << 14); //turn on AFIOEN, IOPAEN, IOPCEN, USART1EN
    // // we enable AFIOEN because we are handing over a job to a peripheral instead of being driven as GPIO.


    // // tx
    // GPIOA_CRH &= ~(0xF << 4); // clear PA9's 4 bit config (bits 4-7 = pin 9, since (9 - 8) * 4 = 4) 
    // GPIOA_CRH |= (0xB << 4); //mode9 = 11, CNF9=10 (output, 50MHz max, alternate-function push-pull)

    // // rx
    // GPIOA_CRH &= ~(0xF << 8); //clear A10's bit config
    // GPIOA_CRH |= (0x4 << 8); //Mode10 = 00, CNF10 = 01 ()

    // // usb to serial workaround
    // GPIOC_CRH &= ~(0xF << 20);
    // GPIOC_CRH |= (0x1 << 20);
    

    // USART1_BRR = 0x341; //9600 baud at 8MHz APB2 clock
    // USART1_CR1 |= (1 << 13) | (1 << 3) | (1 << 2); //UE (USART enable) + TE (transmitter Enable) + enable RE (receiver enable)

    // while (1) {
    //     // uart_send_string("Hello from bare-metal STM32!\r\n");
    //     // for (volatile int i = 0; i < 800000; i++); //crude delay between messages

    //     // uint8_t c = uart_read_byte();
    //     // uart_send_byte(c); //echo it back 

    //     // set test byte
    //     // uart_send_byte(0x55);
    //     // uint8_t got = uart_read_byte();
    //     // if (got == 0x55) {
    //     //     GPIOC_ODR &= ~(1 << 13); // turn on if received correctly
    //     // } else {
    //     //     GPIOC_ODR |= (1 << 13); //mismatch -> led off
    //     // }
    //     // for (volatile int i = 0; i < 800000; i++);

    //     uint8_t c = uart_read_byte();
    //     uart_send_byte(c);
    // }
    gpio_afio_en();
    gpio_clock_en(GPIOA_BASE);
    gpio_clock_en(GPIOC_BASE);

    gpio_set_mode(GPIOA_BASE, 9, GPIO_CNF_AF_OUTPUT_PP_50MHZ);
    gpio_set_mode(GPIOA_BASE, 10, GPIO_CNF_INPUT_FLOAT);

    gpio_set_mode(GPIOC_BASE, 13, GPIO_CNF_OUTPUT_PP_10MHZ); //usb to serial workaround

    uart1_init(0x341);

    while(1) {
        uint8_t c = uart1_read_byte();
        uart1_send_byte(c);
    }
}

// void uart_send_byte(uint8_t byte) {
//     while (!(USART1_SR & (1 << 7))); // wait until TXE (bit 7) = 1; read for new data
//     USART1_DR = byte;
// }

// void uart_send_string(const char *s) {
//     while (*s) uart_send_byte(*s++);
// }

// uint8_t uart_read_byte(void) {
//     while(!(USART1_SR & (1 << 5))); // wait until RXNE = 1; byte has arrived
//     return USART1_DR; //reading DR returns the byte AND clears RXNE
// }