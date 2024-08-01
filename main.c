/*
 * File:   main.c
 * Author: mallo
 *
 * Created on July 30, 2024, 12:19 AM
 */

#include "config_pic18f46k20.h"
#include <xc.h>

#include "LCDDebug.h"

void main(void)
{
    OSCCONbits.IRCF = 0b111;    //Select 16MHz frequency
    TRISAbits.TRISA3 = 0;       //RA3 pin is output (Debug LED)

    _DEBUG_LED_OFF;             //Start with debug LED off
    lcdInit();
    lcdString("LCD Ready");
    lcdCommand(LCD_CMD_CUR_1_0);
    lcdString("ACK: awaiting...");
    while(1)
    {
        _DEBUG_LED_ON;
        __delay_ms(1000);
        _DEBUG_LED_OFF;
        __delay_ms(1000);
    }
    return;
}
