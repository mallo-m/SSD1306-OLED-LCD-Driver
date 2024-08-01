/*
 * File:   LCDDebug.c
 * Author: mallo
 *
 * Created on July 30, 2024, 12:20 AM
 */

#include "LCDDebug.h"

#define LCD_CMD_EN 1 << 1

// https://www.electronicwings.com/8051/lcd16x2-interfacing-in-8-bit-with-8051 
void lcdInit(void)
{
    lcdCommand(LCD_CMD_8BIT);                   //Init in 8-bit mode
    lcdCommand(LCD_CMD_DISPLAY_ON_CUR_OFF);     //Display ON, cursor OFF
    lcdCommand(LCD_CMD_CUR_AUTOINC);            //Cursor auto-increment
    lcdCommand(LCD_CMD_CLS);                    //Clear screen
    lcdCommand(LCD_CMD_CUR_0_0);                //Cursor at 0,0
}

void lcdCommand(unsigned short cmd)
{
    PORTC = cmd;
    PORTDbits.RD1 = 1;
    _delay(10);
    PORTD = 0;
    __delay_ms(500);
}

void lcdChar(unsigned char chr)
{
    PORTC = chr;
    PORTDbits.RD0 = 1;
    PORTDbits.RD1 = 1;
    _delay(10);
    PORTD = 0;
    __delay_ms(10);
}

void lcdString(unsigned char *str)
{
    while (*str != '\0')
    {
        lcdChar(*str);
        str++;
    }
}