#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>

#define PWM_PIN_PB1 1
#define PWM_PIN_PB2 2

void PWM_Init(void);

void Analog_Write(uint8_t pin_pwm, uint8_t duty);

#endif /* PWM_H_ */