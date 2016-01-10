
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "display.h"

//volatile uint8_t lcd_Addr = 0x027;
volatile uint8_t lcd_cols;
volatile uint8_t lcd_rows;
volatile uint8_t dotsize;
volatile uint8_t backlightval;
volatile uint8_t displaycontrol;
volatile uint8_t displaymode;

bool I2C_MasterWrite(uint8_t data, uint8_t addr, I2C_MESSAGE_STATUS* status)
{ int i;
  /* Master Start condition sending. */

  while(!DRV_I2C0_MasterBusIdle());
  if(!DRV_I2C0_MasterStart()) {   return false; }
  DRV_I2C0_WaitForStartComplete();
  while(!DRV_I2C0_MasterBusIdle());

  if (!DRV_I2C0_ByteWrite(addr << 1)&0xFE) { return false;}
  DRV_I2C0_WaitForByteWriteToComplete();

  if (!DRV_I2C0_WriteByteAcknowledged()) { return false;}

  if (!DRV_I2C0_ByteWrite(data)) { return false;}
  DRV_I2C0_WaitForByteWriteToComplete();

  if (!DRV_I2C0_WriteByteAcknowledged()) {return false;}

  if(!DRV_I2C0_MasterStop()){ return false;};

//  *status = I2C_MESSAGE_PENDING;

  return true;
}

void LCD_I2C_WriteData(uint8_t data)
{ I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
  data |= backlightval; int loop = 0;
  while (!I2C_MasterWrite(data, LCD_ADDR, &status) && (loop++ < MAX_IIC_TRY))
  {

  }
  if (loop >= MAX_IIC_TRY)
  {
    debug_LED();
  }
  delayusec(500);
}

void LCD_I2C_PulseEnable(uint8_t data)
{
	LCD_I2C_WriteData(data | En);	// En high
	LCD_I2C_WriteData(data & ~En);	// En low
}

void LCD_I2C_Write4bits(uint8_t value)
{
	LCD_I2C_WriteData(value);
	LCD_I2C_PulseEnable(value);
}

void LCD_I2C_Send(uint8_t value, uint8_t mode) {
	uint8_t highnib = value & 0xf0;
	uint8_t lownib =(value<<4) & 0xf0;
  LCD_I2C_Write4bits((highnib) | mode);
	LCD_I2C_Write4bits((lownib) | mode);
}

// Turn the display on/off (quickly)
void LCD_I2C_NoDisplay() {
	displaycontrol &= ~LCD_DISPLAYON;
	LCD_I2C_Send(LCD_DISPLAYCONTROL | displaycontrol, 0);
}
void LCD_I2C_Display() {
	displaycontrol |= LCD_DISPLAYON;
	LCD_I2C_Send(LCD_DISPLAYCONTROL | displaycontrol, 0);
}

void LCD_I2C_Clear(){
	LCD_I2C_Send(LCD_CLEARDISPLAY, 0); // clear display, set cursor position to zero
	delayusec(100);                    // this command takes a long time!
}

void LCD_I2C_Home(){
	LCD_I2C_Send(LCD_RETURNHOME, 0);   // set cursor position to zero
	delayusec(100);                     // this command takes a long time!
}

void Init_LCD()
{
  uint8_t displayfunction;
  lcd_cols = LCD_COLS;
  lcd_rows = 2;
  dotsize = 0;
  displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
  backlightval = LCD_NOBACKLIGHT;

  if (lcd_rows > 1) displayfunction |= LCD_2LINE;
  // for some 1 line displays you can select a 10 pixel high font
  if ((dotsize != 0) && (lcd_rows == 1)) {
		displayfunction |= LCD_5x10DOTS;
	}
  /* SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
   * according to datasheet, we need at least 40ms after power rises above 2.7V
   * before sending commands.
   */
//	delayms(50);
  delayusec(50000);
	// Now we pull both RS and R/W low to begin commands
  LCD_I2C_WriteData(backlightval);
//	delayms(1000);
  delayusec(1000000);
  //put the LCD into 4 bit mode
	// this is according to the hitachi HD44780 datasheet
	// figure 24, pg 46

	 // we start in 8bit mode, try to set 4 bit mode
   LCD_I2C_Write4bits(0x03 << 4);
//   delayms(5); // wait min 4.1ms
  delayusec(5000);
   // second try
   LCD_I2C_Write4bits(0x03 << 4);
//   delayms(5); // wait min 4.1ms
  delayusec(5000);
   // third go!
   LCD_I2C_Write4bits(0x03 << 4);
//   delayms(1);
  delayusec(1000);
   // finally, set to 4-bit interface
   LCD_I2C_Write4bits(0x02 << 4);
   //delayms(1);
   delayusec(1000);
   // set # lines, font size, etc.
   LCD_I2C_Send(LCD_FUNCTIONSET | displayfunction, 0);

//   delayms(1);
   delayusec(1000);
	// turn the display on with no cursor or blinking default
	 displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
   LCD_I2C_Display();

    // clear it off
   LCD_I2C_Clear();

    // Initialize to default text direction (for roman languages)
   displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    // set the entry mode
   LCD_I2C_Send(LCD_ENTRYMODESET | displaymode, 0);

   LCD_I2C_Home();

}

// Turns the underline cursor on/off
void LCD_I2C_NoCursor() {
	displaycontrol &= ~LCD_CURSORON;
	LCD_I2C_Send(LCD_DISPLAYCONTROL | displaycontrol, 0);
}
void LCD_I2C_Cursor() {
	displaycontrol |= LCD_CURSORON;
	LCD_I2C_Send(LCD_DISPLAYCONTROL | displaycontrol, 0);
}

// Turn on and off the blinking cursor
void LCD_I2C_NoBlink() {
	displaycontrol &= ~LCD_BLINKON;
	LCD_I2C_Send(LCD_DISPLAYCONTROL | displaycontrol, 0);
}
void LCD_I2C_Blink() {
	displaycontrol |= LCD_BLINKON;
	LCD_I2C_Send(LCD_DISPLAYCONTROL | displaycontrol, 0);
}

// These commands scroll the display without changing the RAM
void LCD_I2C_ScrollDisplayLeft(void) {
	LCD_I2C_Send(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT, 0);
}
void LCD_I2C_ScrollDisplayRight(void) {
	LCD_I2C_Send(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT, 0);
}

// This is for text that flows Left to Right
void LCD_I2C_LeftToRight(void) {
	displaymode |= LCD_ENTRYLEFT;
	LCD_I2C_Send(LCD_ENTRYMODESET | displaymode, 0);
}

// This is for text that flows Right to Left
void LCD_I2C_RightToLeft(void) {
	displaymode &= ~LCD_ENTRYLEFT;
	LCD_I2C_Send(LCD_ENTRYMODESET | displaymode, 0);
}

// This will 'right justify' text from the cursor
void LCD_I2C_Autoscroll(void) {
	displaymode |= LCD_ENTRYSHIFTINCREMENT;
	LCD_I2C_Send(LCD_ENTRYMODESET | displaymode, 0);
}

// This will 'left justify' text from the cursor
void LCD_I2C_NoAutoscroll(void) {
	displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	LCD_I2C_Send(LCD_ENTRYMODESET | displaymode, 0);
}

/********** high level commands, for the user! */

void LCD_I2C_SetCursor(uint8_t col, uint8_t row){
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if (row > lcd_rows ) {
		row = lcd_rows - 1;    // we count rows starting w/0
	}
	LCD_I2C_Send(LCD_SETDDRAMADDR | (col + row_offsets[row]), 0);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LCD_I2C_CreateChar(uint8_t location, uint8_t charmap[]) {
  int i;
	location &= 0x7; // we only have 8 locations 0-7
	LCD_I2C_Send(LCD_SETCGRAMADDR | (location << 3), 0);
	for (i = 0; i < 8; i++) {
			LCD_I2C_Send(charmap[i], Rs);
	}
}

// Turn the (optional) backlight off/on
void LCD_I2C_NoBacklight(void) {
	backlightval = LCD_NOBACKLIGHT;
	LCD_I2C_WriteData(0);
}

void LCD_I2C_Backlight(void) {
	backlightval = LCD_BACKLIGHT;
	LCD_I2C_WriteData(0);
}

void LCD_I2C_Cursor_on(){
	LCD_I2C_Cursor();
}

void LCD_I2C_Cursor_off(){
	LCD_I2C_NoCursor();
}

void LCD_I2C_Blink_on(){
	LCD_I2C_Blink();
}

void LCD_I2C_Blink_off(){
	LCD_I2C_NoBlink();
}

void LCD_I2C_Load_custom_character(uint8_t char_num, uint8_t *rows){
  LCD_I2C_CreateChar(char_num, rows);
}

void LCD_I2C_SetBacklight(uint8_t new_val){
	if(new_val){
		LCD_I2C_Backlight();		// turn backlight on
	}else{
		LCD_I2C_NoBacklight();		// turn backlight off
	}
}

void LCD_I2C_PrintStr(const char c[]){
  int i = 0;
  while ((c[i]) != '\0')
  {
    LCD_I2C_Send(c[i++], Rs);
  }
}

void LCD_I2C_PrintBuffer(const char b[], int size)
{ int i;
for (i = 0; i < size; i++)
  {
    LCD_I2C_Send(b[i], Rs);
  }
}

