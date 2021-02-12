#ifndef BUTTON_MANAGER_HPP
#define BUTTON_MANAGER_HPP

#include "button.hpp"
#include "buttonPublisher_I.hpp"
#include <cstdint>
#include <ctime>
#include <map>

#define GPIO_MAX    53
#define BLOCK_SIZE  (4*1024)

// Word offsets of GPIO registers
#define GPLEV0      13
#define GPLEV1      14

// This is the timeout for the event loop.  Be conservative until we know
// what this thing can handle
#define SCAN_RATE   100  // milliseconds

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
  std::map<uint8_t, Button> buttonMap;
  
  // Specified GPIO to interested subscriber
  std::map<uint8_t, ButtonSubscriber_I *> subscriberMap;
};

#endif /* BUTTON_MANAGER_HPP */
