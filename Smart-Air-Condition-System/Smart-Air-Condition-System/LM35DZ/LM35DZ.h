#ifndef LM35DZ_H_
#define LM35DZ_H_

#include <avr/io.h>
#include <stdbool.h>
#include "../PWM/pwm.h"
#include "../INTER/interrupts.h"

#define FIRE_TEMPERATURE 15

#define MODE_AUTO    0
#define MODE_HEATING 2
#define MODE_COOLING 1
#define THRESH 0

#define LM35_ADC_CHANNEL 2

#define HEATING_PIN     PWM_PIN_PB1
#define COOLING_PIN     PWM_PIN_PB2
#define ALARM_PIN       PB3
#define EMERGENCY_PIN	PB5
#define OUTPUT_PORT		PORTB
#define OUTPUT_DDR		DDRB

void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);
uint8_t Read_Temperature(void);
int8_t Temperature_Control(void);

#endif
