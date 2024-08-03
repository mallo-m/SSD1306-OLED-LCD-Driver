/*
 * File:   SSD1306.c
 * Author: mallo
 *
 * Created on August 2, 2024, 2:47 PM
 */

#include "SSD1306.h"
#include "LCDDebug.h"

#define I2C_BaudRate          100000
#define START_PAGE_ADDR           0
#define END_PAGE_ADDR             7     // 7 for 128x64, 3 for 128x32 version
#define START_COLUMN_ADDR         0
#define END_COLUMN_ADDR           127
#define RAM_X_END                 END_COLUMN_ADDR + 1
#define RAM_Y_END                 END_PAGE_ADDR + 1
#define CACHE_SIZE_MEM            (1 + END_PAGE_ADDR) * (1 + END_COLUMN_ADDR)

uint8_t     gotNack  = 0;

static void I2C_WaitForBus()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

static void I2C_TransactionStart()
{
    I2C_WaitForBus();
    SEN = 1;
}

static void I2C_TransactionStop()
{
    I2C_WaitForBus();
    PEN = 1;
}

static void I2C_ByteWrite(unsigned char byte)
{
    if (gotNack)
        return;

    I2C_WaitForBus();
    SSPIF = 0;
    SSPBUF = byte;
    while (!SSPIF);
    SSPIF = 0;
    
    if (ACKSTAT)
    {
        gotNack = 1;
        I2C_TransactionStop();
        lcdClearline(1);
        lcdString("Got NACK ?!?");
        __delay_ms(1000);
    }
}

static void I2C_SendCommand(uint8_t cmd)
{
    uint8_t ack1, ack2, ack3;

    I2C_TransactionStart();
    I2C_ByteWrite((SSD1306_ADDR << 1) | SSD1306_REQ_WRITE);
    I2C_ByteWrite(SSD1306_CONTROL_CMD_STREAM);
    I2C_ByteWrite(cmd);
    I2C_TransactionStop();
}

void SSD1306_Init()
{
    int i = 0;
    unsigned char ack;

    lcdSetCursor(0, 1);
    SSPCON1 = 0x28;
    SSPCON2 = 0x00;
    SSPSTAT = 0x00;
    SSPADD = ((_XTAL_FREQ/4)/I2C_BaudRate) - 1;
    
    I2C_SendCommand(SSD1306_DISPLAY_OFF);
    I2C_SendCommand(SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO);
    I2C_SendCommand(0x80);
    I2C_SendCommand(SSD1306_SET_MULTIPLEX_RATIO);
    I2C_SendCommand(64 - 1);
    I2C_SendCommand(SSD1306_SET_DISPLAY_OFFSET);
    I2C_SendCommand(0x00);
    I2C_SendCommand(SSD1306_SET_START_LINE);
    I2C_SendCommand(SSD1306_CHARGE_PUMP);
    I2C_SendCommand(0x14);
    I2C_SendCommand(SSD1306_MEMORY_ADDR_MODE);
    I2C_SendCommand(0x00);
    I2C_SendCommand(SSD1306_SET_SEGMENT_REMAP | 0x01);
    I2C_SendCommand(SSD1306_COM_SCAN_DIR_DEC);

    I2C_SendCommand(SSD1306_SET_COM_PINS);
    I2C_SendCommand(0x02);
    I2C_SendCommand(SSD1306_SET_CONTRAST_CONTROL);
    I2C_SendCommand(0x8F);
    
    I2C_SendCommand(SSD1306_SET_PRECHARGE_PERIOD);
    I2C_SendCommand(0xF1);
    I2C_SendCommand(SSD1306_SET_VCOM_DESELECT);
    I2C_SendCommand(0x40);
    I2C_SendCommand(SSD1306_DISPLAY_ALL_ON_RESUME);
    I2C_SendCommand(SSD1306_NORMAL_DISPLAY);
    I2C_SendCommand(SSD1306_DEACTIVATE_SCROLL);
    I2C_SendCommand(SSD1306_DISPLAY_ON);
}
