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
    TRISB = OUTPUT;                             //Entire PORT C is output
    TRISDbits.RD0 = OUTPUT;                     //Register Select pin on RD0
    TRISDbits.RD1 = OUTPUT;                     //Enable pin on RD1

    lcdCommand(LCD_CMD_MOD_8BIT);               //Init in 8-bit mode
    lcdCommand(LCD_CMD_DISPLAY_ON_CUR_OFF);     //Display ON, cursor OFF
    lcdCommand(LCD_CMD_CUR_AUTOINC);            //Cursor auto-increment
    lcdCommand(LCD_CMD_CLS);                    //Clear screen
    lcdCommand(LCD_CMD_CUR_0_0);                //Cursor at 0,0
}

void lcdCommand(unsigned short cmd)
{
    PORTB = cmd;
    PORTDbits.RD1 = 1;
    _delay(10);
    PORTD = 0;
    __delay_ms(500);
}

void lcdChar(unsigned char chr)
{
    PORTB = chr;
    PORTDbits.RD0 = 1;
    PORTDbits.RD1 = 1;
    _delay(1);
    PORTD = 0;
    _delay(500);
}

void lcdString(unsigned char *str)
{
    while (*str != '\0')
    {
        lcdChar(*str);
        str++;
    }
}

void lcdSetCursor(unsigned char x, unsigned char y)
{
    if (y == 0)
        lcdCommand(LCD_CMD_CUR_0_0);
    else
        lcdCommand(LCD_CMD_CUR_1_0);
    
    for (int i = 0; i < x; i++) {
        lcdCommand(LCD_CMD_MOV_CUR_RIGHT);
    }
}

void lcdClearline(unsigned char lineno)
{
    lcdSetCursor(0, lineno);
    lcdString("                ");
    lcdSetCursor(0, lineno);
}