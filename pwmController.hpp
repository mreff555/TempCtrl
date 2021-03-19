#ifndef PWMCONTROLLER_HPP
#define PWMCONTROLLER_HPP

#include "common.hpp"
#include <cstdint>

// TODO: FIX THEESE
#define FREQUENCY_MAX 12345
#define FREQUENCY_MIN 0
#define DUTY_CYCLE_MAX 100
#define DUTY_CYCLE_MIN 0

class PwmController
{
  public:
  PwmController();

  ~PwmController();

  PwmController(const PwmController &obj) = delete;

  PwmController operator=(const PwmController&rhs) = delete;

  bool init();

  void startEventLoop(bool &terminate);

  void enable();

  void disable();

  void operator!();

  void operator++();

  void operator+=(const uint8_t value);

  void operator--();

  void operator-=(const uint8_t value);
  
  // TODO:  Still working this out but the current
  // thinking is that the setters for the requency
  // and duty cycle should probably be private,
  // allowing intensity to combine and limit the
  // two factors in a safe and effective way so
  // that setting an intensity from 0 to 100 is
  // all that is required.
  void setIntensity(const uint8_t value);

  uint8_t getIntensity() const;

  void setFrequency(const uint32_t value);

  uint32_t getFrequency() const;

  void setDutyCycle(const uint8_t value);

  uint8_t getDutyCycle() const;

  private:
  EquipmentState pwmState;

  uint8_t intensity;

  uint32_t frequency;

  uint8_t dutyCycle;

};


#endif /* PWMCONTROLLER_HPP */
