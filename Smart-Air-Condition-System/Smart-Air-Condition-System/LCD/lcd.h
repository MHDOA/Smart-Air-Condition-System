#ifndef LCD_H_
#define LCD_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LCD_PORT_DATA   PORTD
#define LCD_DDR_DATA    DDRD
#define LCD_PORT_CTRL   PORTC
#define LCD_DDR_CTRL    DDRC

#define RS PC0
#define EN PC1

void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init();
void lcd_print(char *str);

static void lcd_send_halfbyte(unsigned char halfbit)
{
	LCD_PORT_DATA = (LCD_PORT_DATA & 0x0F) | (halfbit & 0xF0);
	LCD_PORT_CTRL |= (1 << EN);
	_delay_us(1);
	LCD_PORT_CTRL &= ~(1 << EN);
	_delay_us(100);
}

void lcd_cmd(unsigned char cmd)
{
	LCD_PORT_CTRL &= ~(1 << RS);
	lcd_send_halfbyte(cmd);
	lcd_send_halfbyte(cmd << 4);
}

void lcd_data(unsigned char data)
{
	LCD_PORT_CTRL |= (1 << RS);
	lcd_send_halfbyte(data);
	lcd_send_halfbyte(data << 4);
}

void lcd_init()
{
	LCD_DDR_DATA |= 0xF0;    
	LCD_DDR_CTRL |= (1 << RS) | (1 << EN);

	_delay_ms(20);

	lcd_cmd(0x02);   // 4bit
	lcd_cmd(0x28);   // 2 lines
	lcd_cmd(0x0C);   // Display ON, cursor off
	lcd_cmd(0x06);   // Auto-increment
	lcd_cmd(0x01);   // Clear
	_delay_ms(2);
}

void lcd_print(char *str)
{
	while(*str)
	{
		lcd_data(*str++);
	}
}

#endif
