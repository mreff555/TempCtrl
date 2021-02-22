#include "buttonManager.hpp"
#include "buttonSubscriber_I.hpp"
#include "common.hpp"
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <thread>
#include <unistd.h>

ButtonManager::ButtonManager() 
: buttonArr((Button *)calloc(GPIO_MAX, sizeof(Button)))
{
  printf("Initializing Button Manager: %s\n", init() ? "PASS" : "FAIL");
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
  size_t result = 0;
  uint8_t tempGpio = button.getGpio();
  if(tempGpio > 0 && tempGpio <= GPIO_MAX)
  {
    buttonArr[tempGpio] = button;
    ++buttonCount;
  }
  else
  {
    /* Put error here */
    result = -1;
  }
  return result;
}

void ButtonManager::startEventLoop(bool &terminate)
{
  uint8_t tempGpio = 0;
  int newButtonValue = -1;
  time_t holdTime = 0;

  while(terminate == false)
  {
    for(int i = 0; i <= GPIO_MAX; ++i)
    {
      // This SHOULD work for all GPIO's if I remember correctly
      // the memory map that I saw 2 months ago and can't seem to find. 
      tempGpio = buttonArr[i].getGpio();
      if(tempGpio > GPIO_MAX || tempGpio < 1)
      {
         /* Error handling goes here */ 
      }
      else if(tempGpio > 31)
      {
        newButtonValue = (((*(gpio_base + GPLEV1)) >> (tempGpio - 32)) & 0x1);
      }
      else
      {
        newButtonValue = (((*(gpio_base + GPLEV0)) >> tempGpio) & 0x1);
      }
  
      /* Button logic */
      if(buttonArr[tempGpio].getState() == DEFAULT_STATE && newButtonValue == 0) // no change
      {

      }
      else if(buttonArr[tempGpio].getState() == DEFAULT_STATE && newButtonValue == 1) // change to rising
      {
        buttonArr[tempGpio].update(RISING_EDGE);
        printf("%u Button state changed to Rising\n", tempGpio);
      }
      else if(buttonArr[tempGpio].getState() == RISING_EDGE && newButtonValue == 0) // change to falling
      {
        buttonArr[tempGpio].update(FALLING_EDGE);
        holdTime = 0;
        printf("Button state changed to Falling\n");
      }
      else if(buttonArr[tempGpio].getState() == RISING_EDGE && newButtonValue == 1) // hold timer
      {
        holdTime += (time(NULL) - buttonArr[tempGpio].getTimeStamp());
        if(holdTime >= MIN_BUTTON_HOLD_TIME)
        {
          buttonArr[tempGpio].update(LONG_HOLD);
          printf("%u Button state changed to Hold\n", tempGpio);
        }
      }
      else if(buttonArr[tempGpio].getState() == LONG_HOLD && newButtonValue == 0) // change to falling edge
      {
        buttonArr[tempGpio].update(FALLING_EDGE);
        holdTime = 0;
        printf("Button state changed to Falling\n");
      }
      else if(buttonArr[tempGpio].getState() == LONG_HOLD && newButtonValue == 1) // increment hold timer
      {
        holdTime += (time(NULL) - buttonArr[tempGpio].getTimeStamp());
        /* No logic needed here unless we want to add multiple levels of */
        /* hold time sensitivity.                                        */
      }
      else if(buttonArr[tempGpio].getState() == FALLING_EDGE && newButtonValue == 0) // change to default state
      {
        buttonArr[tempGpio].update(DEFAULT_STATE);
      }      
      else if(buttonArr[tempGpio].getState() == FALLING_EDGE && newButtonValue == 1) // change to rising edge
      {
        buttonArr[tempGpio].update(RISING_EDGE);
        printf("%u Button state changed to Rising\n", tempGpio);
      }
      /* These conditions are collectively exhaustive, so I shouldn't need an else statement. */
      notify(tempGpio);
      newButtonValue = -1;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(SCAN_RATE));
  }
}

void ButtonManager::attach(uint8_t gpio, ButtonSubscriber_I *subscriber)
{
  SubscriberEntry se(subscriber, Bitfield(gpio));
  subscriberList.push_back(se);
}
  
void ButtonManager::detach(uint8_t gpio, ButtonSubscriber_I *subscriber)
{
  SubscriberEntry se(subscriber, Bitfield(gpio));
  auto it = std::find(std::begin(subscriberList), std::end(subscriberList), se);
}
  
void ButtonManager::notify(uint8_t gpio)
{
  auto it = subscriberList.begin();
  while(it != subscriberList.end())
  {
    if((*it).second.isSet(gpio))
      (*it).first->update(buttonArr[gpio]);
    ++it;
  }
}
