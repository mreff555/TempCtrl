#include "lcdscreen.hpp"
#include <cstdlib>
#include <cstdio> // for sprintf

LcdScreen::LcdScreen()
{
  if(wiringPiSetup() == -1) exit(1);
  fd = wiringPiI2CSetup(I2C_ADDR);
  lcdInit();
}

LcdScreen::~LcdScreen()
{
  backLightOff();
}

void LcdScreen::backLightOff()
{
  mtx.lock();
  clrLcd();
  int bits = (LCD_CMD | LCD_BACKLIGHT_OFF);
  wiringPiI2CReadReg8(fd, bits);
  lcdToggleEnable(bits);
  mtx.unlock();
}

void LcdScreen::sendActualTemp(const char * buffer)
{
  mtx.lock();
  lcdLoc(LINE1);
  typeLn("Temp: ");
  typeLn(buffer);
  mtx.unlock();
}

void LcdScreen::sendSetPoint(const char * buffer)
{
  mtx.lock();
  lcdLoc(LINE2);
  typeLn("Setpoint: ");
  typeLn(buffer);
  mtx.unlock();
}

// Private
void LcdScreen::lcdToggleEnable(int bits)
{
  // Toggle enable pin on LCD display
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits | ENABLE));
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
  delayMicroseconds(500);
}

void LcdScreen::lcdByte(int bits, int mode)
{
  //Send byte to data pins
  // bits = the data
  // mode = 1 for data, 0 for command
  int bits_high;
  int bits_low;
  // uses the two half byte writes to LCD
  bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT_ON;
  bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT_ON;

  // High bits
  wiringPiI2CReadReg8(fd, bits_high);
  lcdToggleEnable(bits_high);

  // Low bits
  wiringPiI2CReadReg8(fd, bits_low);
  lcdToggleEnable(bits_low);
}

void LcdScreen::lcdInit()
{
  // Initialise display
  lcdByte(0x33, LCD_CMD); // Initialise
  lcdByte(0x32, LCD_CMD); // Initialise
  lcdByte(0x06, LCD_CMD); // Cursor move direction
  lcdByte(0x0C, LCD_CMD); // 0x0F On, Blink Off
  lcdByte(0x28, LCD_CMD); // Data length, number of lines, font size
  lcdByte(0x01, LCD_CMD); // Clear display
  delayMicroseconds(500);
}

// go to location on LCD
void LcdScreen::lcdLoc(int line)
{
  lcdByte(line, LCD_CMD);
}

// clr lcd go home loc 0x80
void LcdScreen::clrLcd(void)
{
  lcdByte(0x01, LCD_CMD);
  lcdByte(0x02, LCD_CMD);
}

// this allows use of any size string
void LcdScreen::typeLn(const char *s)
{
  while ( *s ) lcdByte(*(s++), LCD_CHR);
}

// float to string
void LcdScreen::typeFloat(float myFloat)
{
  char buffer[20];
  sprintf(buffer, "%4.3f",  myFloat);
  typeLn(buffer);
}

void LcdScreen::sendInitMsg()
{
  mtx.lock();

  mtx.unlock();
}

void LcdScreen::sendShutdownMsg()
{
  mtx.lock();

  mtx.unlock();
}
