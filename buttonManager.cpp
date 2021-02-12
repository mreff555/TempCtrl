#include "buttonManager.hpp"
#include "buttonSubscriber_I.hpp"
#include <sys/mman.h>
#include <fcntl.h>
#include <cstdint>
#include <errno.h>
#include <unistd.h>
#include <thread>
#include <chrono>
  
ButtonManager::ButtonManager()
{

}

ButtonManager::~ButtonManager()
{

}

bool ButtonManager::init()
{
  if((fd = open("/dev/gpiomem", O_RDWR | O_SYNC | O_CLOEXEC)) >= 0)
  {
    gpio_base = (uint32_t *)mmap(
      0, 
      BLOCK_SIZE, 
      PROT_READ, 
      MAP_SHARED,
      fd,
      0);
  }
  return true;
}

bool ButtonManager::shutdown()
{
  delete gpio_base;
  close(fd);
  return true;
}

size_t ButtonManager::addButton(Button button)
{
  buttonMap.insert(std::pair<uint8_t, Button>(button.getGpio(), button));
  return buttonMap.size();
}

void ButtonManager::startEventLoop(bool &terminate)
{
  uint8_t tempGpio = 0;

  while(terminate == false)
  {
    for(auto x : buttonMap)
    {
      // This SHOULD work for all GPIO's if I remember correctly
      // the memory map that I saw 2 months ago and can't seem to find. 
      tempGpio = x.second.getGpio();
      if(tempGpio > GPIO_MAX)
      {
        /* Error handling goes here */ 
      }
      else if(tempGpio > 31)
      {
        x.second.update(
          (ButtonState)(((*(gpio_base + GPLEV1)) >> (tempGpio - 32)) & 0x1));
      }
      else
      {
        x.second.update(
          (ButtonState)(((*(gpio_base + GPLEV0)) >> tempGpio) & 0x1));
      }
      notify(tempGpio);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(SCAN_RATE));
  }
}

void ButtonManager::attach(uint8_t gpio, ButtonSubscriber_I *subscriber)
{
  subscriberMap.insert(
    std::pair<uint8_t, ButtonSubscriber_I *>(gpio, subscriber)); 
}
  
void ButtonManager::detach(uint8_t gpio, ButtonSubscriber_I *subscriber)
{

}
  
void ButtonManager::notify(uint8_t gpio)
{

}
