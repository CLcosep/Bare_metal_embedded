#include <stdint.h>

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018)
#define GPIOA_CRH   (*(volatile uint32_t *)0x40010804)
#define USART1_BRR  (*(volatile uint32_t *)0x40013808)
#define USART1_CR1  (*(volatile uint32_t *)0x4001380C)
#define USART1_SR   (*(volatile uint32_t *)0x40013800)
#define USART1_DR   (*(volatile uint32_t *)0x40013804)

void uart_send_byte(uint8_t byte);
void uart_send_string(const char *s);

int main(void) {
    RCC_APB2ENR |= (1 << 0) | (1 << 2) | (1 << 14); //turn on AFIOEN, IOPAEN, USART1EN
    // we enable AFIOEN because we are handing over a job to a peripheral instead of being driven as GPIO.


    GPIOA_CRH &= ~(0xF << 4); // clear PA9's 4 bit config (bits 4-7 = pin 9, since (9 - 8) * 4 = 4) 
    GPIOA_CRH |= (0xB << 4); //mode9 = 11, CNF9=10 (output, 50MHz max, alternate-function push-pull)

    GPIOA_CRH &= ~(0xF << 8); //clear A10's bit config
    GPIOA_CRH |= (0x4 << 8); //Mode10 = 00, CNF10 = 10 ()
    

    USART1_BRR = 0x341; //9600 baud at 8MHz APB2 clock
    USART1_CR1 |= (1 << 13) | (1 << 3); //UE (USART enable) + TE (transmitter Enable)

    while (1) {
        uart_send_string("Hello from bare-metal STM32!\r\n");
        for (volatile int i = 0; i < 800000; i++); //crude delay between messages
    }
}

void uart_send_byte(uint8_t byte) {
    while (!(USART1_SR & (1 << 7))); // wait until TXE (bit 7) = 1; read for new data
    USART1_DR = byte;
}

void uart_send_string(const char *s) {
    while (*s) uart_send_byte(*s++);
}