#ifndef BUTTON_SUBSCRIBER_I_HPP
#define BUTTON_SUBSCRIBER_I_HPP

#include "button.hpp"

class ButtonSubscriber_I
{
public:
  virtual ~ButtonSubscriber_I(){};
  virtual void update(const Button &buttonUpdate) = 0;
};

#endif /* BUTTON_SUBSCRIBER_I_HPP */
