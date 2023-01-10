#ifndef BUTTON_PUBLISHER_I_HPP
#define BUTTON_PUBLISHER_I_HPP

#include <cstdint>

class ButtonSubscriber_I;

class ButtonPublisher_I
{
public:
  virtual ~ButtonPublisher_I(){};
  virtual void attach(uint8_t gpio, ButtonSubscriber_I *subscriber) = 0;
  virtual void detach(uint8_t gpio, ButtonSubscriber_I *subscriber) = 0;
  virtual void notify(uint8_t gpio) = 0;
};

#endif /* BUTTON_PUBLISHER_I_HPP */
