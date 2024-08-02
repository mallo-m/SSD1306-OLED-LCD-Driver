/* 
 * File: LCDDebug.h
 * Author: mmousson@protonmail.com
 * Comments: OLED Driver LCD output debug
 * Revision history: v1.0
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_LCD_DEBUG_H
# define XC_LCD_DEBUG_H

# include <xc.h> // include processor files - each processor file is guarded.  
# include "config_pic18f46k20.h"

/**
    <b>Function prototype: </b>void lcdInit(void);<br/>
    <b>Summary:</b><br/>
    <b>Description:</b>LCD Initialization function<br/>
    <b>Parameters:</b>void<br/>
    <b>Returns:</b>void<br/>
    <b>Example:</b><br/>
    <code>
        lcdInit();<br/>
        //Do stuff<br/>
        return;
    </code>

    <b>Remarks:</b>Call this function at bootup before using the LCD screen
 */
void lcdInit(void);

/**
    <b>Function prototype: </b>lcdChar(unsigned char chr);<br/>
    <b>Summary:</b><br/>
    <b>Description:</b>Put a single char onto LCD screen<br/>
    <b>Parameters:</b><br/>
        <ul>
            <li><b>unsigned char chr</b>: The character to print out</li>
        </ul>
    <b>Returns:</b>void<br/>
    <b>Example:</b><br/>
    <code>
        lcdChar('H');<br/>
        lcdChar('E');<br/>
        lcdChar('L');<br/>
        lcdChar('L');<br/>
        lcdChar('O');
    </code>

    <b>Remarks:</b>Cursor will automatically move to the right if called after lcdInit();
 */
void lcdChar(unsigned char chr);

/**
    <b>Function prototype: </b>lcdCommand(unsigned short cmd);<br/>
    <b>Summary:</b><br/>
    <b>Description: </b>Send an instruction to the screen controller<br/>
    <b>Parameters:</b><br/>
        <ul>
            <li><b>unsigned short cmd</b>: The command to send to the screen controller</li>
        </ul>
    <b>Returns:</b>void<br/>
    <b>Example:</b><br/>
    <code>
        lcdCommand(LCD_CMD_CLS);        //Clear entire screen<br/>
        lcdCommand(LCD_CMD_CUR_0_0);    //Move cursor to top-left corner
    </code>

    <b>Remarks:</b>
 */
void lcdCommand(unsigned short cmd);

/**
    <b>Function prototype: </b>void lcdString(unsigned char *str);<br/>
    <b>Summary:</b><br/>
    <b>Description: </b>Print an entire string to LCD<br/>
    <b>Parameters:</b><br/>
        <ul>
            <li><b>unsigned char *str</b>: The string to display</li>
        </ul>
    <b>Returns:</b>void<br/>
    <b>Example:</b><br/>
    <code>
        lcdString("Hello There");
    </code>

    <b>Remarks:</b>
 */
void lcdString(unsigned char *str);

/**
    <b>Function prototype: </b>void lcdSetCursor(unsigned char x, unsigned char y);<br/>
    <b>Summary:</b><br/>
    <b>Description: </b>Set the cursor to the specified X,Y position (0 offseted)<br/>
    <b>Parameters:</b><br/>
        <ul>
            <li><b>unsigned char x</b>: Horizontal position of the cursor (must be between 0 and 15 inclusive)</li>
            <li><b>unsigned char y</b>: Vertical position of the cursor (0 for the top line, 1 for the bottom line) </li>
        </ul>
    <b>Returns:</b>void<br/>
    <b>Example:</b><br/>
    <code>
        lcdSetCursor(7, 1);     //Move cursor to the 8th character of the bottom row
    </code>

    <b>Remarks:</b>
 */
void lcdSetCursor(unsigned char x, unsigned char y);

void lcdClearline(unsigned char lineno);

// LCD 16x2 commands used
// https://www.electronicwings.com/sensors-modules/lcd-16x2-display-module
# define LCD_CMD_MOD_4BIT 0x28
# define LCD_CMD_MOD_8BIT 0x38
# define LCD_CMD_DISPLAY_ON_CUR_OFF 0x0c
# define LCD_CMD_CUR_AUTOINC 0x06
# define LCD_CMD_CLS 0x01
# define LCD_CMD_CUR_0_0 0x80
# define LCD_CMD_CUR_1_0 0xc0
# define LCD_CMD_MOV_CUR_LEFT 0x10
# define LCD_CMD_MOV_CUR_RIGHT 0x14

#endif	/* XC_HEADER_TEMPLATE_H */
