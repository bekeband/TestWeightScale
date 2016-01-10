/* 
 * File:   display.h
 * Author: user
 *
 * Created on 2016. január 6., 8:57
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

// *****************************************************************************
// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set:
//    DL = 1; 8-bit interface data
//    N = 0; 1-line display
//    F = 0; 5x8 dot character font
// 3. Display on/off control:
//    D = 0; Display off
//    C = 0; Cursor off
//    B = 0; Blinking off
// 4. Entry mode set:
//    I/D = 1; Increment by 1
//    S = 0; No shift
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// LiquidCrystal constructor is called).

  // commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En 0b00000100  // Enable bit
#define Rw 0b00000010  // Read/Write bit
#define Rs 0b00000001  // Register select bit

#define LCD_COLS  16
#define LCD_I2C_PORT I2C_ID_4
#define MAX_IIC_TRY 5
#define LCD_ADDR  0x027

typedef enum
{
    I2C_MESSAGE_COMPLETE,
    I2C_MESSAGE_FAIL,
    I2C_MESSAGE_PENDING,
    I2C_STUCK_START,
    I2C_MESSAGE_ADDRESS_NO_ACK,
    I2C_DATA_NO_ACK,
    I2C_LOST_STATE
} I2C_MESSAGE_STATUS;

void Init_LCD();
void LCD_I2C_Backlight();
void LCD_I2C_NoBacklight();
void LCD_I2C_PrintStr(const char c[]);
void LCD_I2C_PrintBuffer(const char b[], int size);
void LCD_I2C_SetCursor(uint8_t col, uint8_t row);
void LCD_I2C_Display();
void LCD_I2C_Clear();
void LCD_I2C_Home();

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */

