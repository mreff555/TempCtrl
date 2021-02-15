#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "common.hpp"
#include <ctime>
#include <cstdint>

class Button
{
  public:
  Button(uint8_t gpio);

  ~Button();

  void update(ButtonState newValue);

  uint8_t getGpio() const;

  ButtonState getState() const;

  time_t getTimeStamp() const;

  private:
  uint8_t gpioId;
  ButtonState buttonState;
  time_t timeStamp;
};

#endif /* BUTTON_HPP */
