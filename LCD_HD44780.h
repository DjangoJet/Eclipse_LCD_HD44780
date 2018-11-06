/*
 * main.c
 *
 *  Created on: 31 paŸ 2018
 *      Author: Mike
 */
#ifndef HD44780_H_
#define HD44780_H_

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

#define LCD_DDR DDRB
#define PortLED PORTB
#define RS 0
#define EN 1
#define LCD_Dx4 4
#define LCD_Dx5 5
#define LCD_Dx6 6
#define LCD_Dx7 7
#define ROW 2
#define COL 16

void LCD_SendChar(int8_t data);
void LCD_Clear();
void LCD_SwitchOn();
void LCD_SetChar(int8_t row, int8_t col, char letter);
void LCD_SetString(int8_t row, int8_t col, char *text);

#endif /* HD44780_H_ */