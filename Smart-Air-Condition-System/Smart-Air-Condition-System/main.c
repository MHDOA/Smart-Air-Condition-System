#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD/lcd.h"


int main(void)
{
	lcd_init();
	unsigned char message[] = "Hello";
	while (1)
	{
		lcd_clear();
		lcd_print(message);
		_delay_ms(500);
		
	}
}
