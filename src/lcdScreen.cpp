#include <lcdScreen.hpp>
#include <cstdio>
#include <cstdlib>
#include <string>

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
LcdScreen::LcdScreen()
{
  fd = wiringPiI2CSetup(I2C_ADDR);
  printf("Initializing Lcd Screen Controller: %s\n",
         lcdInit() ? "PASS" : "FAIL");
}

LcdScreen::~LcdScreen() { backLightOff(); }

/*********************************************
 * Function: backlightoff                     *
 *                                            *
 * Description:                               *
 * Clears the LCD screen and turns the back   *
 * lighting off.                              *
 **********************************************/
void LcdScreen::backLightOff()
{
  mtx.lock();
  clrLcd();
  int bits = (LCD_CMD | LCD_BACKLIGHT_OFF);
  wiringPiI2CReadReg8(fd, bits);
  lcdToggleEnable(bits);
  mtx.unlock();
}

/*********************************************
 * Function: sendTemp                         *
 *                                            *
 * Description:                               *
 * Format temperature output to the LCD       *
 * screen based on input temp and desired     *
 * scale.                                     *
 **********************************************/
void LcdScreen::sendTemp(float temp, TScale_E scale)
{
  mtx.lock();
  std::string strbuf;
  switch (scale)
  {
  case CELSIUS:
    strbuf += std::to_string(temp);
    strbuf.erase(strbuf.find('.', 0) + 4);
    strbuf += "C";
    break;
  case FARENHEIT:
    strbuf += std::to_string(32.000 + temp * 9.000 / 5.000);
    strbuf.erase(strbuf.find('.', 0) + 4);
    strbuf += "F";
    break;
  case KELVIN:
    strbuf += std::to_string(temp + 273.150);
    strbuf.erase(strbuf.find('.', 0) + 4);
    strbuf += "K";
    break;
  case RANKINE:
    strbuf += std::to_string((temp + 273.150) * 9.000 / 5.000);
    strbuf.erase(strbuf.find('.', 0) + 4);
    strbuf += "R";
    break;
  }

  lcdLoc(LCD_LINE1);
  typeLn("                ");
  lcdLoc(LCD_LINE1);
  typeLn("Temp: ");
  typeLn(strbuf.c_str());
  mtx.unlock();
}

/*********************************************
 * Function: sendNewMode                      *
 *                                            *
 * Description:                               *
 * Calls mode function based on mode input    *
 **********************************************/
void LcdScreen::sendNewMode(InputMode_E newMode, float setPoint, TScale_E scale)
{
  switch (newMode)
  {
  case SETPOINT:
    sendSetPoint(setPoint, scale);
    break;
  case SET_SCALE:
    sendScale(scale);
    break;
  case LOAD_PROFILE:
    sendLoadProfile();
    break;
  case PID_TUNE:
    sendPidTune();
    break;
  default:
    /* Unspecified mode */
    break;
  }
}

/*********************************************
 * Function: sendSetPoint                     *
 *                                            *
 * Description:                               *
 * Formats setpoint output for LCD screen     *
 * based on input temperature and scale       *
 **********************************************/
void LcdScreen::sendSetPoint(const float setPoint, const TScale_E scale)
{
  mtx.lock();
  std::string strbuf;
  switch (scale)
  {
  case CELSIUS:
    strbuf += std::to_string(setPoint);
    strbuf.erase(strbuf.find('.', 0) + 4);
    strbuf += "C";
    break;
  case FARENHEIT:
    strbuf += std::to_string(32.000 + setPoint * 9.000 / 5.000);
    strbuf.erase(strbuf.find('.', 0) + 4);
    strbuf += "F";
    break;
  case KELVIN:
    strbuf += std::to_string(setPoint + 273.150);
    strbuf.erase(strbuf.find('.', 0) + 4);
    strbuf += "K";
    break;
  case RANKINE:
    strbuf += std::to_string((setPoint + 273.150) * 9.000 / 5.000);
    strbuf.erase(strbuf.find('.', 0) + 4);
    strbuf += "R";
    break;
  }
  lcdLoc(LCD_LINE2);
  typeLn("                ");
  lcdLoc(LCD_LINE2);
  typeLn("SetPt: ");
  typeLn(strbuf.c_str());
  mtx.unlock();
}

/*********************************************
 * Function: sendScale                        *
 *                                            *
 * Description:                               *
 * Formats scale output for LCD screen        *
 **********************************************/
void LcdScreen::sendScale(const TScale_E scale)
{
  mtx.lock();
  std::string strbuf;
  switch (scale)
  {
  case CELSIUS:
    strbuf = "Celsius";
    break;

  case FARENHEIT:
    strbuf = "Farenheit";
    break;

  case KELVIN:
    strbuf = "Kelvin";
    break;

  case RANKINE:
    strbuf = "Rankine";
    break;
  }
  lcdLoc(LCD_LINE2);
  typeLn("                ");
  lcdLoc(LCD_LINE2);
  typeLn("Scale: ");
  typeLn(strbuf.c_str());
  mtx.unlock();
}

/*********************************************
 * Function: sendLoadProfile                  *
 *                                            *
 * Description:                               *
 * Formats load profile output for LCD screen *
 **********************************************/
void LcdScreen::sendLoadProfile()
{
  mtx.lock();
  lcdLoc(LCD_LINE2);
  typeLn("                ");
  lcdLoc(LCD_LINE2);
  typeLn("Profile: ");
  /* Write me!! */
  mtx.unlock();
}

/*********************************************
 * Function: sendPidTune                      *
 *                                            *
 * Description:                               *
 * Formats PID tuning output for LCD screen   *
 **********************************************/
void LcdScreen::sendPidTune()
{
  mtx.lock();
  lcdLoc(LCD_LINE2);
  typeLn("                ");
  lcdLoc(LCD_LINE2);
  typeLn("PID Tune? ");
  /* Write me!! */
  mtx.unlock();
}

// Private
void LcdScreen::lcdToggleEnable(int bits)
{
  // Toggle enable pin on LCD display
  delayMicroseconds(LCD_DELAY);
  wiringPiI2CReadReg8(fd, (bits | ENABLE));
  delayMicroseconds(LCD_DELAY);
  wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
  delayMicroseconds(LCD_DELAY);
}

void LcdScreen::lcdByte(int bits, int mode)
{
  // Send byte to data pins
  //  bits = the data
  //  mode = 1 for data, 0 for command
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

bool LcdScreen::lcdInit()
{
  bool success = false;
  // Initialise display
  lcdByte(0x33, LCD_CMD);                // Initialise
  lcdByte(0x32, LCD_CMD);                // Initialise
  lcdByte(LCD_CUR_INC, LCD_CMD);         // Cursor move direction
  lcdByte(LCD_DISP_ON_CUR_OFF, LCD_CMD); // 0x0F On, Blink Off
  lcdByte(LCD_4BIT, LCD_CMD);  // Data length, number of lines, font size
  lcdByte(LCD_CLEAR, LCD_CMD); // Clear display
  delayMicroseconds(LCD_DELAY);
  success = true;
  return success;
}

// go to location on LCD
void LcdScreen::lcdLoc(int line) { lcdByte(line, LCD_CMD); }

// clr lcd go home loc 0x80
void LcdScreen::clrLcd(void)
{
  lcdByte(0x01, LCD_CMD);
  lcdByte(0x02, LCD_CMD);
}

// this allows use of any size string
void LcdScreen::typeLn(const char *s)
{
  while (*s)
    lcdByte(*(s++), LCD_CHR);
}

// float to string
void LcdScreen::typeFloat(float myFloat)
{
  char buffer[20];
  sprintf(buffer, "%4.3f", myFloat);
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
