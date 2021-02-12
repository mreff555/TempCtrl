#include "button.hpp"

Button::Button(uint8_t gpio) 
: gpioId(gpio),
buttonState(DEFAULT_STATE), 
timeStamp(time(NULL))
{
  
}

Button::~Button()
{

}

void Button::update(ButtonState newValue)
{
  gpioId = newValue;
  timeStamp = time(NULL);
}

uint8_t Button::getGpio() const
{
  return gpioId;
}

ButtonState Button::getState() const
{
  return buttonState; 
}

time_t Button::getTimeStamp() const
{
  return timeStamp;
}

