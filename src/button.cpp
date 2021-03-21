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
  buttonState = newValue;
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
  
/***************************************************/
/* If gpio's match, update timestamp and state and */
/* return true.  Otherwise return false            */
/***************************************************/
bool Button::operator << (const Button &rhs)
{
  bool success = false;
  if(this->gpioId == rhs.getGpio())
  {
    this->buttonState = rhs.getState();
    this->timeStamp = rhs.getTimeStamp();
    success = true;
  }
  return success;
}

/***************************************************/
/* Returns true if the the button's time stamp is  */
/* newer than the one it is being compared to.     */
/***************************************************/
// bool Button::operator > (const Button &rhs)
// {
//   return getTimeStamp() > rhs.getTimeStamp();
// }

