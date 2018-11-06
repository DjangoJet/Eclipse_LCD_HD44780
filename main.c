/*
 * main.c
 *
 *  Created on: 31 paü 2018
 *      Author: Mike
 */
#include "LCD_HD44780.h"

int main(void)
{

	LCD_SwitchOn();



	char tekst[] = "HelloWorld";


	// LCD_SetString(1,3, tekst);

	LCD_SetString(1,2,tekst);

    while(1)
    {
    	;
    }

    return 0;
}


