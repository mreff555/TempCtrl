#ifndef COMMON_HPP
#define COMMON_HPP

#include <list>
#include <cstdint>
#include <string>
#include <ctime>
#include <utility>

class Bitfield;
class ButtonSubscriber_I;

#define GPIO_MAX    53
#define BLOCK_SIZE  (4*1024)

// Word offsets of GPIO registers
#define GPLEV0      13
#define GPLEV1      14

// This is the timeout for the event loop.  Be conservative until we know
// what this thing can handle
// TODO: should probably rename this.  It was fine as it was when these macros
// were located in the buttonManager.  Now it is poorly named
#define SCAN_RATE   5  // milliseconds

// This is the minimum time a button must be held to handle the interaction
// as a held button.
#define MIN_BUTTON_HOLD_TIME    500  // milliseconds

typedef std::pair<ButtonSubscriber_I *, Bitfield> SubscriberEntry;
typedef std::list<SubscriberEntry> SubscriberList;

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
