#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#define BAUD 9600
#define F_CPU 4000000UL

void uart_init(void);
void uart_send_char(char c);
void uart_send_str(const char *s);

#endif /* UART_H_ */