#include "LM35DZ.h"

void ADC_Init(void)
{
    OUTPUT_DDR |= (1 << ALARM_PIN) | (1 << EMERGENCY_PIN);
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

uint16_t ADC_Read(uint8_t channel)
{
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}

uint8_t Read_Temperature(void)
{
    uint16_t adc_value = ADC_Read(LM35_ADC_CHANNEL);
    uint8_t tempC = (uint8_t)(adc_value * 0.488);
    if(tempC > FIRE_TEMPERATURE && alarm)
    {
        OUTPUT_PORT |= (1 << ALARM_PIN) | (1 << EMERGENCY_PIN);
    }
    else
    {
        OUTPUT_PORT &= ~((1 << ALARM_PIN) | (1 << EMERGENCY_PIN));
    }
    return tempC;
}

int8_t Temperature_Control(void)
{
    uint8_t temp = Read_Temperature();
    int8_t diff = (int8_t)temp - (int8_t)target_temp;
		
    if((diff > THRESH && mode==MODE_AUTO) || (mode==MODE_COOLING && diff > 0))
        Analog_Write(COOLING_PIN, diff);
	else
		Analog_Write(COOLING_PIN, 0);
		
    if((diff < -THRESH && mode==MODE_AUTO) || (mode==MODE_HEATING && diff < 0))
        Analog_Write(HEATING_PIN, -diff);
	else
		Analog_Write(HEATING_PIN, 0);
    return diff;
}
