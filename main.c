/*
 * File:   main.c
 * Author: mallo
 *
 * Created on July 30, 2024, 12:19 AM
 */

#include "config_pic18f46k20.h"
#include <xc.h>

#include "LCDDebug.h"
#include "SSD1306.h"

#define SSPCONN1_SSPEN (1 << 5)
#define SSPCONN1_SSPM_I2C_MASTER_MODE 0b1000

void main(void)
{
    OSCCONbits.IRCF = 0b111;    //Select 16MHz frequency
    TRISAbits.TRISA3 = 0;       //RA3 pin is output (Debug LED)

    _DEBUG_LED_OFF;             //Start with debug LED off
    lcdInit();
    lcdString("System boot OK");
    lcdSetCursor(0, 1);
    lcdString("ACK: awaiting...");

    SSD1306_Init();
    
    lcdSetCursor(0, 1);
    if (SSPCON1bits.SSPEN) {
        lcdClearline(1);
        lcdString("Awaiting packets");
    } else {
        lcdClearline(1);
        lcdString("I2C failed");
    }
    
    while(1)
    {
        _DEBUG_LED_ON;
        __delay_ms(1000);
        _DEBUG_LED_OFF;
        __delay_ms(1000);
    }
    return;
}
