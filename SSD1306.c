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
uint8_t     screen[8][128] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
uint8_t     pagesDispatcher[64] = {
    0,                                          //1
    4,                                          //2
    0,                                          //3
    4,                                          //4
    0,                                          //5
    4,                                          //6
    0,                                          //7
    4,                                          //8
    0,                                          //9
    4,                                          //10
    0,                                          //11
    4,                                          //12
    0,                                          //13
    4,                                          //14
    0,                                          //15
    4,                                          //16
    1,                                          //17
    5,                                          //18
    1,                                          //19
    5,                                          //20
    1,                                          //21
    5,                                          //22
    1,                                          //23
    5,                                          //24
    1,                                          //25
    5,                                          //26
    1,                                          //27
    5,                                          //28
    1,                                          //29
    5,                                          //30
    1,                                          //31
    5,                                          //32
    2,                                          //33
    6,                                          //34
    2,                                          //35
    6,                                          //36
    2,                                          //37
    6,                                          //38
    2,                                          //39
    6,                                          //40
    2,                                          //41
    6,                                          //42
    2,                                          //43
    6,                                          //44
    2,                                          //45
    6,                                          //46
    2,                                          //47
    6,                                          //48
    3,                                          //49
    7,                                          //50
    3,                                          //51
    7,                                          //52
    3,                                          //53
    7,                                          //54
    3,                                          //55
    7,                                          //56
    3,                                          //57
    7,                                          //58
    3,                                          //59
    7,                                          //60
    3,                                          //61
    7,                                          //62
    3,                                          //63
    7                                           //64
};

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

static void I2C_SendBuffer(uint8_t *page)
{
    I2C_TransactionStart();
    I2C_ByteWrite((SSD1306_ADDR << 1) | SSD1306_REQ_WRITE);
    I2C_ByteWrite(SSD1306_CONTROL_DATA_STREAM);
    for (int i = 0; i < 128; i++)
    {
        I2C_ByteWrite(page[i]);
    }
    I2C_TransactionStop();
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

static void SSD1306_SelectPage(uint8_t pageno)
{
    uint8_t pagenoSelect;
    
    pagenoSelect = (0xB0 | pageno);
    I2C_SendCommand(pagenoSelect);
    I2C_SendCommand(0x00);
    I2C_SendCommand(0x10);
}

static void SSD1306_ClearPage(uint8_t pageno)
{
    SSD1306_SelectPage(pageno);
    I2C_SendBuffer(0x0);
}

static void SSD1306_UpdateScreen()
{
    for (int y = 0; y < 8; y++)
    {
        SSD1306_SelectPage(y);
        I2C_SendBuffer(screen[y]);
    }
}

static void SSD1306_ConvertCoordinates(uint8_t x, uint8_t y, uint8_t *pageno, uint8_t *byteno, uint8_t *bitno)
{
    *byteno = x - 1;
    *pageno = pagesDispatcher[y - 1];
    *bitno = ((y - 1) / 2) % 8;
}

static void SSD1306_PutPixel(uint8_t x, uint8_t y, uint8_t value)
{
    uint8_t pageno;
    uint8_t byteno;
    uint8_t bitno;

    SSD1306_ConvertCoordinates(x, y, &pageno, &byteno, &bitno);
    screen[pageno][byteno] |= (value << bitno);
    if (x % 4 == 0)
        SSD1306_UpdateScreen();
}

static void SSD1306_DrawLine(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2)
{
    int16_t D;
    int16_t delta_x, delta_y;
    int16_t trace_x, trace_y;
    
    trace_x = trace_y = 1;
    delta_x = x2 - x1;
    delta_y = y2 - y1;
    if (delta_x < 0)
    {
        delta_x = -delta_x;
        trace_x = -trace_x;
    }
    if (delta_y < 0)
    {
        delta_y = -delta_y;
        trace_y = -trace_y;
    }
    
    if (delta_y < delta_x)
    {
        D = (delta_y << 1) - delta_x;
        SSD1306_PutPixel(x1, y1, SSD1306_PIXEL_ON);
        while (x1 != x2)
        {
            x1 += trace_x;
            if (D >= 0)
            {
                y1 += trace_y;
                D -= 2 * delta_x;
            }
            D += 2 * delta_y;
            SSD1306_PutPixel(x1, y1, SSD1306_PIXEL_ON);
        }
    }
    else
    {
        D = delta_y - (delta_x << 1);
        SSD1306_PutPixel(x1, y1, SSD1306_PIXEL_ON);
        while (y1 != y2)
        {
            y1 += trace_y;
            if (D <= 0)
            {
                x1 += trace_x;
                D += 2 * delta_y;
            }
            D -= 2 * delta_x;
            SSD1306_PutPixel(x1, y1, SSD1306_PIXEL_ON);
        }
    }
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
    
    __delay_ms(2000);

    SSD1306_UpdateScreen();
    lcdClearline(1);
    lcdString("Screen Updated !");
    __delay_ms(1000);
    
    SSD1306_DrawLine(32, 64, 17, 64);
    SSD1306_DrawLine(96, 64, 17, 64);
    SSD1306_DrawLine(32, 37, 16, 1);
    SSD1306_DrawLine(96, 91, 16, 1);
    SSD1306_DrawLine(37, 58, 1, 1);
    SSD1306_DrawLine(59, 64, 1, 16);
    SSD1306_DrawLine(64, 69, 16, 1);
    SSD1306_DrawLine(69, 91, 1, 1);
    SSD1306_UpdateScreen();

    lcdClearline(1);
    lcdString("Pixel put ?");
    __delay_ms(3000);
}
