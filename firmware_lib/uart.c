#include "uart.h"

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018)
#define USART1_BRR  (*(volatile uint32_t *)0x40013808)
#define USART1_CR1  (*(volatile uint32_t *)0x4001380C)
#define USART1_SR   (*(volatile uint32_t *)0x40013800)
#define USART1_DR   (*(volatile uint32_t *)0x40013804)

void uart1_init(uint16_t brr_value) {
    RCC_APB2ENR |= (1 << 14);
    USART1_BRR = brr_value;
    USART1_CR1 |= (1 << 13) | (1 << 3) | (1 << 2);
}

void uart1_send_byte(uint8_t byte) {
    while(!(USART1_SR & (1 << 7)));
    USART1_DR = byte;
}

void uart1_send_string(const char *s) {
    while(*s) uart1_send_byte(*s++);
}

uint8_t uart1_read_byte(void) {
    while (!(USART1_SR & (1 << 5)));
    return USART1_DR;
}