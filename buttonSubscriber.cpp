#include "buttonSubscriber.hpp"
#include "buttonManager.hpp"
class Button;

// int ButtonSubscriber::static_number_ = 0;

ButtonSubscriber::ButtonSubscriber(ButtonManager &_buttonManager) 
: buttonManager(_buttonManager),
menuButton(26)
{
  buttonManager.addButton(menuButton);
  subscribe(menuButton.getGpio());
}

ButtonSubscriber::~ButtonSubscriber()
{
  unsubscribe(menuButton.getGpio());
}

void ButtonSubscriber::update(const Button &buttonUpdate)
{
  // TODO: Everything with the subscription should be good
  // up to this point.  The problem is that we need a method
  // of knowning which button to pass the update to. We
  // will probably need a method of iterating through
  // buttons in this class and comparing. 
}

void ButtonSubscriber::subscribe(uint8_t gpio)
{
  this->buttonManager.attach(gpio, this); 
}

void ButtonSubscriber::unsubscribe(uint8_t gpio = 0)
{
  this->buttonManager.detach(gpio, this);
}
