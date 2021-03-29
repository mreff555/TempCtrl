#ifndef BUTTON_MANAGER_HPP
#define BUTTON_MANAGER_HPP

#include "button.hpp"
#include "buttonPublisher_I.hpp"
#include "bitfield.hpp"
#include <cstdint>
#include <ctime>

class ButtonSubscriber_I;

class ButtonManager : public ButtonPublisher_I
{
  public:
  ButtonManager();

  virtual ~ButtonManager();

  bool init();

  bool shutdown();
  
  size_t addButton(Button button);

  void startEventLoop(bool &terminate);

  void attach(uint8_t gpio, ButtonSubscriber_I *subscriber) override;
  
  void detach(uint8_t gpio, ButtonSubscriber_I *subscriber) override;
  
  void notify(uint8_t gpio) override;

  private:

  int fd;

  volatile uint32_t *gpio_base;

  // Specified GPIO to actual button map
  Button *buttonArr;
  size_t buttonCount;
  
  SubscriberList subscriberList;
  
};

#endif /* BUTTON_MANAGER_HPP */
