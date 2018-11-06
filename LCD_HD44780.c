/*
 * main.c
 *
 *  Created on: 31 paŸ 2018
 *      Author: Mike
 */

#include "LCD_HD44780.h"

void LCD_SendChar(int8_t data)
{
	// wlaczenie linii ENABLE
	PortLED |= (1<<EN);

	//wys³anie 4 starszych bitów
	PortLED = (data & 0xf0)|(PortLED & 0x0f);

	// potwierdzenie wys³ana danych poprzez opadniêcie ENABLE
	PortLED &= ~(1<<EN);

	// odczekanie jednego cyklu
	asm volatile("nop");

	PortLED |= (1<<EN);
	//wys³anie 4 m³odszych bitów
	PortLED = ((data & 0x0f)<<4)|(PortLED & 0x0f);
	PortLED &= ~(1<<EN);

	// odczekanie niezbêdnej d³ugoœci czasu na potwierdzenie wprowadzenia danych
	_delay_us(40);
}

void LCD_Clear()
{
	// przestawia na linii RS wartoœæ na 0 po to by wys³aæ komendê a nie dane
	PortLED &= ~(1<<RS);
	// wysy³amy polecenie wyczyszczenia LCD
	LCD_SendChar(1);

	// przestawia liniê RS na wartoœæ 1 odpowiadaj¹c¹ wprowadzaniu danych
	PortLED |= (1<<RS);

	// maksymalny czas oczekiwania na wyczyszczenie ekranu LCD
	_delay_ms(1.64);
}

void LCD_SwitchOn()
{
	// ustawienie kierunku wyjœciowego dla wszystkich linii
	LCD_DDR = (0xf0)|(_BV(RS))|(_BV(EN));

	// ustawienie pocz¹tkowego stanu niskiego na wszystkich liniach
	PortLED = 0;


	// rozpoczêcie wysy³ania komendy
	PortLED &= ~(1<<RS);
	// ustawienie parametrów wyœwietlacza
	// BIT 4: 1 - 8 linii, 0 - 4 linie,
	// BIT 3: 1 - 2 wiersze, 0 - 1 wiersz
	// BIT 2: 0 - wymiar znaku 5x8; 1 - wymiar 5x10
	LCD_SendChar(0b00101000);
	PortLED |= (1<<RS);

	PortLED &= ~(1<<RS);
	// BIT 2 - tryb pracy wyœwietlacza (inkrementowanie zapisu danych)
	// BIT1: 1 - przesuniêcie okna, 0 - przesuniêcie kursora
	LCD_SendChar(0b00000110);
	PortLED |= (1<<RS);


	PortLED &= ~(1<<RS);
	// BIT2: 1 - wyœwietlacz w³¹czony, 0 - wy³¹czony
	// BIT1: 1 - w³¹czenie wyœwietlania kursora, 0 - kursor niewidoczny
	// BIT0: 1 - kursor miga, 0 - kursor nie miga
	LCD_SendChar(0b00001100);
	PortLED |= (1<<RS);

	LCD_Clear();
}

void LCD_SetChar(int8_t row, int8_t col, char letter)
{

	int Position = 0;
	int i;
	if(row > 1)
	{
		Position += 40;
	}

	Position += col-1;

	for(i=0;i<Position;i++)
	{
		PortLED &= ~(1<<RS);
		LCD_SendChar(0b00010100);
		PortLED |= (1<<RS);
	}

    LCD_SendChar(letter);

	for(i=0;i<Position+1;i++)
	{
		PortLED &= ~(1<<RS);
		LCD_SendChar(0b00010000);
		PortLED |= (1<<RS);
	}
}

void LCD_SetString(int8_t row, int8_t col, char *text)
{
    int i = 0;

    for(i=0; !(text[i]=='\0'); i++)
    {
    	LCD_SetChar(row, col+i, text[i]);
    	LCD_SetChar(row+1, col, i+48);
    	_delay_ms(700);
    }

}