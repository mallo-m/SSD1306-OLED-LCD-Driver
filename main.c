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
    TRISC = 0;                  //Entire PORT C is output
    TRISDbits.RD0 = 0;          //Register Select pin on RD0
    TRISDbits.RD1 = 0;          //Enable pin on RD1

    PORTAbits.RA3 = 0;          //Start with debug LED off
    lcdInit();
    lcdString("ACK Received !");
    while(1)
    {
        PORTAbits.RA3 = 1;
        __delay_ms(1000);
        PORTAbits.RA3 = 0;
        __delay_ms(1000);
    }
    return;
}
