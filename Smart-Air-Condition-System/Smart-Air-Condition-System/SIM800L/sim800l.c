#include "sim800l.h"


void sim800_init(void) {
	_delay_ms(2000);
	uart_send_str("AT\r\n");
	_delay_ms(1000);
	uart_send_str("ATE0\r\n");     // echo off
	_delay_ms(500);
	uart_send_str("AT+CMGF=1\r\n"); // SMS text mode
	_delay_ms(2500);
}

void sim800_call(const char *phone) {
	uart_send_str("ATD");
	uart_send_str(phone);
	uart_send_str(";\r\n");
}

void sim800_hangup(void) {
	uart_send_str("ATH\r\n");
}

void sim800_send_sms(const char *phone, const char *msg) {
	uart_send_str("AT+CMGS=\"");
	uart_send_str(phone);
	uart_send_str("\"\r\n");
	_delay_ms(1000);

	uart_send_str(msg);
	_delay_ms(200);

	uart_send_char(26);   // CTRL+Z
	_delay_ms(10000);
}