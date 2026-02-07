#include "interrupts.h"

static volatile uint8_t int0_event = 0;
static volatile uint8_t int1_event = 0;

volatile int16_t target_temp = 25;
volatile uint8_t mode        = 0;
volatile bool alarm          = false;

ISR(INT0_vect) {
	int0_event = 1;
}

ISR(INT1_vect) {
	int1_event = 1;
}

void init_interrupts(void) {
	cli();
	DDRD  &= ~((1 << PIN_MODE) | (1 << PIN_ALARM));
	PORTD |=  (1 << PIN_MODE) | (1 << PIN_ALARM);

	DDRB  &= ~((1 << PIN_UP) | (1 << PIN_DOWN));
	PORTB |=  (1 << PIN_UP) | (1 << PIN_DOWN);

	MCUCR |= (1 << ISC01) | (1 << ISC11);
	GICR  |= (1 << INT0) | (1 << INT1);
	sei();
}

void process_key_events(void) {
	if (int0_event) {
		int0_event = 0;
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			mode++;
			if (mode > 2) mode = 0;
		}
	}

	if (int1_event) {
		int1_event = 0;
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			alarm = !alarm;
		}
	}

	if (!(PINB & (1 << PIN_UP))) {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			if (target_temp < SETTEMP_MAX) target_temp++;
		}
		loop_until_bit_is_set(PINB, PIN_UP);
	}

	if (!(PINB & (1 << PIN_DOWN))) {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			if (target_temp > SETTEMP_MIN) target_temp--;
		}
		loop_until_bit_is_set(PINB, PIN_DOWN);
	}
}