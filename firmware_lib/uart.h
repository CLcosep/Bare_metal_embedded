#ifndef UART_H
#define UART_H
#include <stdint.h>

void uart1_init(uint16_t brr_value);
void uart1_send_byte(uint8_t byte);
void uart1_send_string(const char *s);
uint8_t uart1_read_byte(void);

#endif