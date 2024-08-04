/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_SSD1306_H
#define	XC_SSD1306_H

# include <xc.h> // include processor files - each processor file is guarded.

# define SSD1306_ADDR                           0b0111100
# define SSD1306_REQ_WRITE                      0x0
# define SSD1306_REQ_READ                       0x1
# define SSD1306_CONTROL_CMD_STREAM             0b00000000
# define SSD1306_CONTROL_DATA_STREAM            0b01000000

# define SSD1306_DISPLAY_OFF                    0xAE
# define SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO    0xD5
# define SSD1306_SET_MULTIPLEX_RATIO            0xA8
# define SSD1306_SET_DISPLAY_OFFSET             0xD3
# define SSD1306_SET_START_LINE                 0x40
# define SSD1306_CHARGE_PUMP                    0x8D
# define SSD1306_MEMORY_ADDR_MODE               0x20
# define SSD1306_SET_SEGMENT_REMAP              0xA0
# define SSD1306_COM_SCAN_DIR_DEC               0xC8
# define SSD1306_SET_COM_PINS                   0xDA
# define SSD1306_SET_CONTRAST_CONTROL           0x81
# define SSD1306_SET_PRECHARGE_PERIOD           0xD9
# define SSD1306_SET_VCOM_DESELECT              0xDB
# define SSD1306_DISPLAY_ALL_ON_RESUME          0xA4
# define SSD1306_NORMAL_DISPLAY                 0xA6
# define SSD1306_DEACTIVATE_SCROLL              0x2E
# define SSD1306_DISPLAY_ON                     0xAF
# define SSD1306_SET_COLUMN_ADDR                0x21

# define SSD1306_PIXEL_ON                       0b1
# define SSD1306_PIXEL_OFF                      0b0

void SSD1306_Init();

#endif	/* XC_HEADER_TEMPLATE_H */

