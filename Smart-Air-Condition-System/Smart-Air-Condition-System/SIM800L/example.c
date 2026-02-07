#define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "sim800l.h"
#include "../UART/uart.h"

int sim800_exam(void) {
	uart_init();
	sim800_init();

	_delay_ms(2000);

	// send SMS
	sim800_send_sms("09135363582", "ALARM!!!! FIRE DETECTED!!!!!");

	_delay_ms(5000);

	// call
	sim800_call("09135363582");

	_delay_ms(20000);
	sim800_hangup();

	while (1);
}
