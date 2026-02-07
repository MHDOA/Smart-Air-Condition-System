#include "pwm.h"
#include <avr/io.h>

void PWM_Init(void) {
    DDRB |= (1 << PB1) | (1 << PB2); // OC1A, OC1B

    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B = (1 << WGM12) | (1 << CS11);
}

void Analog_Write(uint8_t pin_pwm, uint8_t duty) {
    if(duty > 255) duty = 255;

    if(pin_pwm == PWM_PIN_PB1)
        OCR1A = duty;
    else if(pin_pwm == PWM_PIN_PB2)
        OCR1B = duty;
}