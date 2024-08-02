/*
 * File:   SSD1306.c
 * Author: mallo
 *
 * Created on August 2, 2024, 2:47 PM
 */

#include "SSD1306.h"
#include "LCDDebug.h"

#define I2C_BaudRate          100000

static void I2C_MasterWait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

static void I2C_MasterStart()
{
    I2C_MasterWait();
    SEN = 1;
}

static void I2C_MasterStop()
{
    I2C_MasterWait();
    PEN = 1;
}

static unsigned char I2C_MasterWrite(unsigned char byte)
{
    I2C_MasterWait();
    SSPIF = 0;
    SSPBUF = byte;
    while (!SSPIF);
    SSPIF = 0;
    return (ACKSTAT);
}

void SSD1306_Init()
{
    unsigned char result;

    lcdSetCursor(0, 1);
    
    SSPCON1 = 0x28;
    SSPCON2 = 0x00;
    SSPSTAT = 0x00;
    SSPADD = ((_XTAL_FREQ/4)/I2C_BaudRate) - 1;
    //SCL_bit = 1;
    //SDA_bit = 1;

    //I2C_MasterStart();
    //result = I2C_MasterWrite(SSD1306_ADDR);
    //I2C_MasterStop();
    
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
    SEN = 1;
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
    SSPIF = 0;
    SSPBUF = 0b01111000;
    while (!SSPIF);
    SSPIF = 0;
    result = ACKSTAT;
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
    PEN = 1;

    if (result) {
        lcdClearline(1);
        lcdString("NACK");
    } else {
        lcdClearline(1);
        lcdString("ACK Received!");
    }
    __delay_ms(1000);
}
