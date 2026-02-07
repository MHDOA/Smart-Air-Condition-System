#ifndef LCD_H_
#define LCD_H_

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
void lcd_init(void);
void lcd_print(const char *str);
void lcd_clear(void);
void lcd_set_cursor(unsigned char col, unsigned char row);

#endif

