#include <button.hpp>

Button::Button(uint8_t gpio)
    : gpioId(gpio), buttonState(DEFAULT_STATE), timeStamp(time(NULL))
{
}

void Button::update(ButtonState newValue)
{
  buttonState = newValue;
  timeStamp = time(NULL);
}

uint8_t Button::getGpio() const { return gpioId; }

ButtonState Button::getState() const { return buttonState; }

time_t Button::getTimeStamp() const { return timeStamp; }

bool Button::operator<<(const Button &rhs)
{
  bool success = false;
  if (this->gpioId == rhs.getGpio())
  {
    this->buttonState = rhs.getState();
    this->timeStamp = rhs.getTimeStamp();
    success = true;
  }
  return success;
}
