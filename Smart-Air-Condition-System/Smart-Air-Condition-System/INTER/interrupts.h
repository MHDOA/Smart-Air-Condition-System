#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdint.h>
#include <stdbool.h>

#define PIN_MODE    PD2
#define PIN_ALARM   PD3
#define PIN_UP      PB0
#define PIN_DOWN    PB4

#define SETTEMP_MIN 5
#define SETTEMP_MAX 40

extern volatile int16_t target_temp;
extern volatile uint8_t mode;
extern volatile bool alarm;

void init_interrupts(void);
void process_key_events(void);

#endif