/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File: LCDDebug.h
 * Author: mmousson@protonmail.com
 * Comments: OLED Driver LCD output debug
 * Revision history: v1.0
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_LCD_DEBUG_H
# define	XC_LCD_DEBUG_H

# include <xc.h> // include processor files - each processor file is guarded.  
# include "config_pic18f46k20.h"

// TODO Insert C++ class definitions if appropriate

/**
    <b>Function prototype:</b>void lcdInit(void);<br/>
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
void lcdChar(unsigned char chr);
void lcdCommand(unsigned short cmd);
void lcdString(unsigned char *str);

# define LCD_CMD_8BIT 0x38
# define LCD_CMD_DISPLAY_ON_CUR_OFF 0x0c
# define LCD_CMD_CUR_AUTOINC 0x06
# define LCD_CMD_CLS 0x01
# define LCD_CMD_CUR_0_0 0x80

# ifdef	__cplusplus
extern "C" {
# endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

# ifdef	__cplusplus
}
# endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */
