#include "uart.h"

#define UBRR_VAL ((F_CPU/16/BAUD)-1)

void uart_init(void) {
	UBRRH = (unsigned char)(UBRR_VAL>>8);
	UBRRL = (unsigned char)UBRR_VAL;
	UCSRB = (1<<TXEN);                     // only TX
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0); // 8bit
}

void uart_send_char(char c) {
	while (!(UCSRA & (1<<UDRE)));
	UDR = c;
}

void uart_send_str(const char *s) {
	while (*s) uart_send_char(*s++);
}