#include "buttonSubscriber.hpp"
#include "buttonManager.hpp"
#include <cstdio>
class Button;

ButtonSubscriber::ButtonSubscriber(ButtonManager &_buttonManager)
    : buttonManager(_buttonManager)
{
  registeredButton.push_back(Button(26)); // Menu button
  buttonManager.addButton(registeredButton.back());
  subscribe(registeredButton.back().getGpio());
}

ButtonSubscriber::~ButtonSubscriber()
{
  auto it = registeredButton.begin();
  while (it != registeredButton.end())
  {
    unsubscribe(it->getGpio());
    ++it;
  }
}

void ButtonSubscriber::update(const Button &buttonUpdate)
{
  auto it = registeredButton.begin();
  while (it != registeredButton.end())
  {
    // The button << overload copies data for matching button ID's only.
    // This isn't 100% intuitive, but I'm going to do it anyway.
    (*it) << buttonUpdate;
    ++it;
  }
}

void ButtonSubscriber::subscribe(uint8_t gpio)
{
  this->buttonManager.attach(gpio, this);
}

void ButtonSubscriber::unsubscribe(uint8_t gpio = 0)
{
  this->buttonManager.detach(gpio, this);
}
