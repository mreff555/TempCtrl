#ifndef LCD_SCREEN_HPP
#define LCD_SCREEN_HPP

#include <common.hpp>
#include <mutex>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define LCD_DELAY 250 // microseconds

#define I2C_ADDR 0x27 // I2C device address
#define LCD_CHR 1     // Mode - Sending data
#define LCD_CMD 0     // Mode - Sending command

// Commands
#define LCD_CLEAR 0x01
#define LCD_CUR_DEC 0x04
#define LCD_CUR_INC 0x06
#define LCD_LINE1 0x80 // 1st line
#define LCD_LINE2 0xC0 // 2nd line
#define LCD_DISP_ON_CUR_OFF 0x0C
#define LCD_BACKLIGHT_ON 0x08
#define LCD_BACKLIGHT_OFF 0x00
#define LCD_4BIT 0x28
#define LCD_8BIT 0x38
#define ENABLE 0b00000100 // Enable bit

/*********************************************
 * Class: LcdScreen                           *
 *                                            *
 * Description:                               *
 * The purpose of this class is strictly for  *
 * sending thread safe data to the screen.    *
 * logic in this class should be limited to   *
 * unit conversions for items that will be    *
 * displayed                                  *
 **********************************************/
class LcdScreen
{
public:
  LcdScreen();

  virtual ~LcdScreen(void);

  /*********************************************
   * Function: backlightoff                     *
   *                                            *
   * Description:                               *
   * Clears the LCD screen and turns the back   *
   * lighting off.                              *
   **********************************************/
  void backLightOff(void);

  /*********************************************
   * Function: sendTemp                         *
   *                                            *
   * Description:                               *
   * Formats temperature output to the LCD      *
   * screen based on input temp and desired     *
   * scale.                                     *
   **********************************************/
  void sendTemp(float temp, TScale_E scale);

  /*********************************************
   * Function: sendNewMode                      *
   *                                            *
   * Description:                               *
   * Calls mode function based on mode input    *
   **********************************************/
  void sendNewMode(InputMode_E newMode, float setPoint, TScale_E scale);

  /*********************************************
   * Function: sendSetPoint                     *
   *                                            *
   * Description:                               *
   * Formats setpoint output for LCD screen     *
   * based on input temperature and scale       *
   **********************************************/
  void sendSetPoint(const float setPoint, const TScale_E scale);

  /*********************************************
   * Function: sendScale                        *
   *                                            *
   * Description:                               *
   * Formats scale output for LCD screen        *
   **********************************************/
  void sendScale(const TScale_E scale);

  /*********************************************
   * Function: sendLoadProfile                  *
   *                                            *
   * Description:                               *
   * Formats load profile output for LCD screen *
   **********************************************/
  void sendLoadProfile();

  /*********************************************
   * Function: sendPidTune                      *
   *                                            *
   * Description:                               *
   * Formats PID tuning output for LCD screen   *
   **********************************************/
  void sendPidTune();

private:
  void lcdToggleEnable(int bits);

  void lcdByte(int bits, int mode);

  void clrLcd(void);

  bool lcdInit(void);

  void lcdLoc(int line);

  void typeLn(const char *s);

  void typeFloat(float myFloat);

  void sendInitMsg(void);

  void sendShutdownMsg(void);

  int fd;
  std::mutex mtx;
};

#endif /* LCD_SCREEN_HPP */
