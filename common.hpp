#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <ctime>
enum ButtonState
{
  DEFAULT_STATE,
  RISING_EDGE,
  LONG_HOLD,
  FALLING_EDGE
};

/***********************************************
*  A structure for holding a single data point *
*  of temperature in degrees celsius, as well  *
*  as the temp probe ID and a time stamp.      *
************************************************/

struct TempStruct
{
  time_t      ts;
  std::string id; 
  float       temp;
};

enum TScale_E
{
  CELSIUS,
  FARENHEIT,
  KELVIN,
  RANKINE,
  MAX_VALUE_TSCALE
};

#define DEFAULT_TEMP_SCALE FARENHEIT

enum InputMode_E
{
  SETPOINT,
  LOAD_PROFILE,
  PID_TUNE,
  MAX_VALUE_INPUT_MODE
}; 
#endif /* COMMON_HPP */
