#include "lcd.h"

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

void lcd_print(const char *str)
{
	while(*str)
	{
		lcd_data((unsigned char)*str++);
	}
}

void lcd_clear(){
	lcd_cmd(0x01);
	_delay_ms(2);
}

void lcd_set_cursor(unsigned char col, unsigned char row)
{
	unsigned char address;
	
	if (row == 0)
	{
		// first row
		address = 0x80 + col;
	}
	else
	{
		// second row
		address = 0xC0 + col;
	}
	
	lcd_cmd(address);
}