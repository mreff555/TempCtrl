#include <button.hpp>

Button::Button(uint8_t gpio, std::string buttonDesc)
: gpioId(gpio), buttonState(DEFAULT_STATE), timeStamp(time(NULL))
{
  if(buttonDesc == "")
  {
    this->mButtonDesc = std::string("gpio ") + std::to_string(gpio);
  }
  else
  {
    this->mButtonDesc = buttonDesc;
  }
}

void Button::update(ButtonState newValue)
{
  buttonState = newValue;
  timeStamp = time(NULL);
}

uint8_t Button::getGpio() const { return gpioId; }

ButtonState Button::getState() const { return buttonState; }

time_t Button::getTimeStamp() const { return timeStamp; }

std::string Button::getButtonDesc() const { return mButtonDesc; }

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
