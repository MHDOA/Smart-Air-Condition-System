#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <stdio.h>
#include <string.h>
#include "LCD/lcd.h"


/* pins */
#define PIN_MODE PD2   // INT0
#define PIN_UP   PB0   // PCINT0
#define PIN_DOWN PB1   // PCINT1

/* shared state */
volatile uint8_t int0_event = 0;       // MODE flag
volatile uint8_t pcint_event = 0;      // UP/DOWN flag
volatile uint8_t pcint_snapshot = 0xFF;// snapshot of PB

volatile int16_t setTemp = 25;         // user temperature
volatile uint8_t mode = 0;             // 0=HEATER, 1=COOLER



ISR(INT0_vect) { 
    int0_event = 1;  // MODE pressed
}

ISR(PCINT0_vect) {
    pcint_snapshot = PINB; // UP/DOWN snapshot
    pcint_event = 1;
}


static void process_key_events(void)
{
    uint32_t now = millis();

    /* ---- MODE ---- */
    if (int0_event) {
        int0_event = 0;
        mode = (mode == 0) ? 1 : 0;  // toggle mode
    }

    /* ---- UP / DOWN ---- */
    if (pcint_event) {
        uint8_t snap = pcint_snapshot; 
        pcint_event = 0;

        uint8_t cur_up   = !(snap & (1<<PIN_UP));   // active-low
        uint8_t cur_down = !(snap & (1<<PIN_DOWN));

        if (cur_up) {
            setTemp++;   // increase temperature
            if(setTemp > SETTEMP_MAX) setTemp = SETTEMP_MAX;
        }
        if (cur_down) {
            setTemp--;   // decrease temperature
            if(setTemp < SETTEMP_MIN) setTemp = SETTEMP_MIN;
        }
    }
}


// in main We should have :
// while(1) {
//     process_key_events(); 
//     .... other functions
// }

