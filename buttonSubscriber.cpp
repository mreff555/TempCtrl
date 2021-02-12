#include "buttonSubscriber.hpp"
#include "buttonManager.hpp"
class Button;

int ButtonSubscriber::static_number_ = 0;

ButtonSubscriber::ButtonSubscriber(ButtonManager &publisher) 
: buttonPublisher(publisher)
{

}

void ButtonSubscriber::update(const Button &buttonUpdate)
{

}

void ButtonSubscriber::subscribe(uint8_t gpio)
{
  this->buttonPublisher.attach(gpio, this); 
}

void ButtonSubscriber::unsubscribe(uint8_t gpio = 0)
{
  this->buttonPublisher.detach(gpio, this);
}
