#ifndef COMMON_HPP
#define COMMON_HPP

#include <list>
#include <cstdint>
#include <string>
#include <ctime>
#include <utility>

class Bitfield;
class ButtonSubscriber_I;

// Current offsets are ONLY for the RPI 4.  We are making use of
// the /dev/gpiomem device so that programs do not have to be invoked
// with sudo.  For that reason the offset for the gpio from the mapped
// location will be 0x0.  The only reason we need the GPIO_BASE macro
// is to calculate offsets within the GPIO memory range.

#define BCM2835_PERI_BASE 0x20000000   // RPI 1
#define BCM2708_PERI_BASE 0x3f000000   // RPI 2 + 3
#define BCM2711_PERI_BASE 0x7e200000   // RPI 4
#define GPIO_MAX    53
#define BLOCK_SIZE  (4*1024)

// Word offsets of GPIO registers
#define GPLEV0      13
#define GPLEV1      14

// This is the timeout for the event loop.  Be conservative until we know
// what this thing can handle.
#define SCAN_RATE   5  // milliseconds

// This is the minimum time a button must be held to handle the interaction
// as a held button.
#define MIN_BUTTON_HOLD_TIME    200  // milliseconds

// This is the buffer size for historical temperature data.
#define TEMP_HISTORY_SIZE 50

// Maximum and minimum temperatures are in celsius
#define TEMP_MAX_SP 100

#define TEMP_MIN_SP 20

// If the Data Manager is unable to get thermocouple input during initialization.
// This is the default value in celsius, which temperature will be set to.
#define TEMP_SP_DEFAULT 20

#define W1_DEV_ROOT "/sys/bus/w1/devices/w1_bus_master1/"

#define W1_SLAVE_COUNT W1_DEV_ROOT "w1_master_slave_count"

#define W1_SLAVES W1_DEV_ROOT "w1_master_slaves"

#define POLL_FREQ 1000

typedef std::pair<ButtonSubscriber_I *, Bitfield> SubscriberEntry;
typedef std::list<SubscriberEntry> SubscriberList;

enum ButtonState
{
  DEFAULT_STATE,
  RISING_EDGE,
  LONG_HOLD,
  FALLING_EDGE
};

enum EquipmentState
{
  DISABLED,
  ENABLED
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
  SET_SCALE,
  LOAD_PROFILE,
  PID_TUNE,
  INPUT_MODE_MAX_VALUE
}; 

struct PidDataStruct
{
  std::string name;
  std::string description;
  float kP;
  float kI;
  float kD;
  float volume;
  /* Need thermodynamic coefficient of some type */
};

#endif /* COMMON_HPP */
