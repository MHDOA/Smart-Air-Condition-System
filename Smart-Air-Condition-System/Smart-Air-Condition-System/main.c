#define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

#include "UART/uart.h"
#include "SIM800L/sim800l.h"
#include "LCD/lcd.h"
#include "LM35DZ/lm35dz.h"
#include "PWM/pwm.h"
#include "INTER/interrupts.h"

#define ALARM_MSG "***ALARM-FIRE***"
#define PHONE_N "09135363582"

static void int_to_char(uint8_t val, char *buf) {
	buf[0] = '0' + (val / 10);
	buf[1] = '0' + (val % 10);
	buf[2] = '\0';
}


int main(void) {
	
	lcd_init();
	
	lcd_print("ADC initialize");
	ADC_Init();
	
	lcd_clear();
	lcd_print("PWM initialize");
	PWM_Init();
	
	lcd_clear();
	lcd_print("Interrup init");
	init_interrupts();
	_delay_ms(10000);
	
	lcd_clear();
	lcd_print("UART initialize");
	uart_init();
	
	lcd_clear();
	lcd_print("SIM initialize");
	sim800_init();
	
		
	lcd_clear();
	lcd_print("final initialize");
	_delay_ms(1000);
	lcd_clear();
	
	while (1) {
		process_key_events();
		
		uint8_t c = Read_Temperature();
		Temperature_Control();
		
		char buf[8];
		
		if(c > FIRE_TEMPERATURE && alarm){
			lcd_clear();
			
			lcd_print("T:");
			int_to_char(c, buf);
			lcd_print(buf);
			
			lcd_set_cursor(0,1);
			lcd_print(ALARM_MSG);
			sim800_send_sms(PHONE_N, ALARM_MSG);
			
			_delay_ms(2000);
			
			lcd_clear();
			lcd_print("CALL TO");
			lcd_set_cursor(0,1);
			lcd_print(PHONE_N);
			sim800_call(PHONE_N);
			
			_delay_ms(10000);
		}
		

		lcd_clear();
		lcd_print("T:");
		int_to_char(c, buf);
		lcd_print(buf);
		
		lcd_print(" Set:");
		int_to_char(target_temp, buf);
		lcd_print(buf);
		
		lcd_set_cursor(0, 1);
		lcd_print("Mode:");
		switch(mode){
			case 0:
				lcd_print("AUTO");
				break;
			case 1:
				lcd_print("COOL");
				break;
			case 2:
				lcd_print("HEAT");
				break;
			}
		
		lcd_set_cursor(12,0);
		lcd_print("AL:");
		if(alarm) lcd_print("E");
		else lcd_print("D");
		
		
		_delay_ms(200);
	}
}