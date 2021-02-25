#ifndef LCD_SCREEN_HPP
#define LCD_SCREEN_HPP

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <mutex>

#define I2C_ADDR   0x27 // I2C device address

// Define some device constants
#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command

#define LINE1  0x80 // 1st line
#define LINE2  0xC0 // 2nd line

#define LCD_BACKLIGHT_ON   0x08  
#define LCD_BACKLIGHT_OFF  0x00  

#define ENABLE  0b00000100 // Enable bit

/***********************************************
* Class: LcdScreen                             *
*                                              *
* Description:                                 *
* The ONLY purpose of this class is to send    *
* atomic safe instructions to the LCD screen.  *
* Any logic operations should be done          *
* elsewhere.                                   *
************************************************/
class LcdScreen// : public ButtonSubscriber 
{
  public:
  LcdScreen();

  virtual ~LcdScreen(void);

  void clear(void);

  void backLightOff(void);
  
  void sendActualTemp(const char * buffer);

  void sendSetPoint(const char * buffer);

  private:
  void lcdToggleEnable(int bits);

  void lcdByte(int bits, int mode);
  
  void clrLcd(void);

  void lcdInit(void);

  void lcdLoc(int line);

  void typeLn(const char *s);

  void typeFloat(float myFloat);

  void sendInitMsg(void);

  void sendShutdownMsg(void);

  int fd;
  std::mutex mtx;
};

#endif /* LCD_SCREEN_HPP */
