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

static const uint8_t Font_5_8[][5] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00 }, // 20 space
    { 0x00, 0x00, 0x6F, 0x00, 0x00 }, // 21 !
    { 0x00, 0x07, 0x00, 0x07, 0x00 }, // 22 "
    { 0x14, 0x7f, 0x14, 0x7f, 0x14 }, // 23 #
    { 0x24, 0x2a, 0x7f, 0x2a, 0x12 }, // 24 $
    { 0x23, 0x13, 0x08, 0x64, 0x62 }, // 25 %
    { 0x36, 0x49, 0x55, 0x22, 0x50 }, // 26 &
    { 0x00, 0x05, 0x03, 0x00, 0x00 }, // 27 '
    { 0x00, 0x1c, 0x22, 0x41, 0x00 }, // 28 (
    { 0x00, 0x41, 0x22, 0x1c, 0x00 }, // 29 )
    { 0x14, 0x08, 0x3e, 0x08, 0x14 }, // 2a *
    { 0x08, 0x08, 0x3e, 0x08, 0x08 }, // 2b +
    { 0x00, 0x50, 0x30, 0x00, 0x00 }, // 2c ,
    { 0x08, 0x08, 0x08, 0x08, 0x08 }, // 2d -
    { 0x00, 0x60, 0x60, 0x00, 0x00 }, // 2e .
    { 0x20, 0x10, 0x08, 0x04, 0x02 }, // 2f /
    { 0x3e, 0x51, 0x49, 0x45, 0x3e }, // 30 0
    { 0x00, 0x42, 0x7f, 0x40, 0x00 }, // 31 1
    { 0x42, 0x61, 0x51, 0x49, 0x46 }, // 32 2
    { 0x21, 0x41, 0x45, 0x4b, 0x31 }, // 33 3
    { 0x18, 0x14, 0x12, 0x7f, 0x10 }, // 34 4
    { 0x27, 0x45, 0x45, 0x45, 0x39 }, // 35 5
    { 0x3c, 0x4a, 0x49, 0x49, 0x30 }, // 36 6
    { 0x01, 0x71, 0x09, 0x05, 0x03 }, // 37 7
    { 0x36, 0x49, 0x49, 0x49, 0x36 }, // 38 8
    { 0x06, 0x49, 0x49, 0x29, 0x1e }, // 39 9
    { 0x00, 0x36, 0x36, 0x00, 0x00 }, // 3a :
    { 0x00, 0x56, 0x36, 0x00, 0x00 }, // 3b ;
    { 0x08, 0x14, 0x22, 0x41, 0x00 }, // 3c <
    { 0x14, 0x14, 0x14, 0x14, 0x14 }, // 3d =
    { 0x00, 0x41, 0x22, 0x14, 0x08 }, // 3e >
    { 0x02, 0x01, 0x51, 0x09, 0x06 }, // 3f ?
    { 0x32, 0x49, 0x79, 0x41, 0x3e }, // 40 @
    { 0x7e, 0x11, 0x11, 0x11, 0x7e }, // 41 A
    { 0x7f, 0x49, 0x49, 0x49, 0x36 }, // 42 B
    { 0x3e, 0x41, 0x41, 0x41, 0x22 }, // 43 C
    { 0x7f, 0x41, 0x41, 0x22, 0x1c }, // 44 D
    { 0x7f, 0x49, 0x49, 0x49, 0x41 }, // 45 E
    { 0x7f, 0x09, 0x09, 0x09, 0x01 }, // 46 F
    { 0x3e, 0x41, 0x49, 0x49, 0x7a }, // 47 G
    { 0x7f, 0x08, 0x08, 0x08, 0x7f }, // 48 H
    { 0x00, 0x41, 0x7f, 0x41, 0x00 }, // 49 I
    { 0x20, 0x40, 0x41, 0x3f, 0x01 }, // 4a J
    { 0x7f, 0x08, 0x14, 0x22, 0x41 }, // 4b K
    { 0x7f, 0x40, 0x40, 0x40, 0x40 }, // 4c L
    { 0x7f, 0x02, 0x0c, 0x02, 0x7f }, // 4d M
    { 0x7f, 0x04, 0x08, 0x10, 0x7f }, // 4e N
    { 0x3e, 0x41, 0x41, 0x41, 0x3e }, // 4f O
    { 0x7f, 0x09, 0x09, 0x09, 0x06 }, // 50 P
    { 0x3e, 0x41, 0x51, 0x21, 0x5e }, // 51 Q
    { 0x7f, 0x09, 0x19, 0x29, 0x46 }, // 52 R
    { 0x46, 0x49, 0x49, 0x49, 0x31 }, // 53 S
    { 0x01, 0x01, 0x7f, 0x01, 0x01 }, // 54 T
    { 0x3f, 0x40, 0x40, 0x40, 0x3f }, // 55 U
    { 0x1f, 0x20, 0x40, 0x20, 0x1f }, // 56 V
    { 0x3f, 0x40, 0x38, 0x40, 0x3f }, // 57 W
    { 0x63, 0x14, 0x08, 0x14, 0x63 }, // 58 X
    { 0x07, 0x08, 0x70, 0x08, 0x07 }, // 59 Y
    { 0x61, 0x51, 0x49, 0x45, 0x43 }, // 5a Z
    { 0x00, 0x7f, 0x41, 0x41, 0x00 }, // 5b [
    { 0x02, 0x04, 0x08, 0x10, 0x20 }, // 5c backslash
    { 0x00, 0x41, 0x41, 0x7f, 0x00 }, // 5d ]
    { 0x04, 0x02, 0x01, 0x02, 0x04 }, // 5e ^
    { 0x40, 0x40, 0x40, 0x40, 0x40 }, // 5f _
    { 0x00, 0x01, 0x02, 0x04, 0x00 }, // 60 `
    { 0x20, 0x54, 0x54, 0x54, 0x78 }, // 61 a
    { 0x7f, 0x48, 0x44, 0x44, 0x38 }, // 62 b
    { 0x38, 0x44, 0x44, 0x44, 0x20 }, // 63 c
    { 0x38, 0x44, 0x44, 0x48, 0x7f }, // 64 d
    { 0x38, 0x54, 0x54, 0x54, 0x18 }, // 65 e
    { 0x08, 0x7e, 0x09, 0x01, 0x02 }, // 66 f
    { 0x0c, 0x52, 0x52, 0x52, 0x3e }, // 67 g
    { 0x7f, 0x08, 0x04, 0x04, 0x78 }, // 68 h
    { 0x00, 0x44, 0x7d, 0x40, 0x00 }, // 69 i
    { 0x20, 0x40, 0x44, 0x3d, 0x00 }, // 6a j
    { 0x7f, 0x10, 0x28, 0x44, 0x00 }, // 6b k
    { 0x00, 0x41, 0x7f, 0x40, 0x00 }, // 6c l
    { 0x7c, 0x04, 0x18, 0x04, 0x78 }, // 6d m
    { 0x7c, 0x08, 0x04, 0x04, 0x78 }, // 6e n
    { 0x38, 0x44, 0x44, 0x44, 0x38 }, // 6f o
    { 0x7c, 0x14, 0x14, 0x14, 0x08 }, // 70 p
    { 0x08, 0x14, 0x14, 0x14, 0x7c }, // 71 q
    { 0x7c, 0x08, 0x04, 0x04, 0x08 }, // 72 r
    { 0x48, 0x54, 0x54, 0x54, 0x20 }, // 73 s
    { 0x04, 0x3f, 0x44, 0x40, 0x20 }, // 74 t
    { 0x3c, 0x40, 0x40, 0x20, 0x7c }, // 75 u
    { 0x1c, 0x20, 0x40, 0x20, 0x1c }, // 76 v
    { 0x3c, 0x40, 0x30, 0x40, 0x3c }, // 77 w
    { 0x44, 0x28, 0x10, 0x28, 0x44 }, // 78 x
    { 0x0c, 0x50, 0x50, 0x50, 0x3c }, // 79 y
    { 0x44, 0x64, 0x54, 0x4c, 0x44 }, // 7a z
    { 0x00, 0x08, 0x36, 0x41, 0x00 }, // 7b {
    { 0x00, 0x00, 0x7f, 0x00, 0x00 }, // 7c |
    { 0x00, 0x41, 0x36, 0x08, 0x00 }, // 7d }
    { 0x10, 0x08, 0x08, 0x10, 0x08 }, // 7e ~
    { 0x00, 0x00, 0x00, 0x00, 0x00 }  // 7f
  };

void SSD1306_Init();

#endif	/* XC_HEADER_TEMPLATE_H */

