/**
 * @file buttonManager.hpp
 * @author Dan Feerst (feerstd@gmail.com)
 * @brief Used to manage button subscribler list. 
 * @version 0.1
 * @date 2022-04-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
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
  /**
   * @brief Construct a new Button Manager object
   * 
   */
  ButtonManager();

  /**
   * @brief Destroy the Button Manager object
   * 
   */
  virtual ~ButtonManager() = default;

  /**
   * @brief 
   * 
   * @return true 
   * @return false 
   */
  bool init();

  /**
   * @brief 
   * 
   * @return true 
   * @return false 
   */
  bool shutdown();
  
  /**
   * @brief 
   * 
   * @param button 
   * @return size_t 
   */
  size_t addButton(Button button);

  /**
   * @brief 
   * 
   * @param terminate 
   */
  void startEventLoop(bool &terminate);

  /**
   * @brief 
   * 
   * @param gpio 
   * @param subscriber 
   */
  void attach(uint8_t gpio, ButtonSubscriber_I *subscriber) override;
  
  /**
   * @brief 
   * 
   * @param gpio 
   * @param subscriber 
   */
  void detach(uint8_t gpio, ButtonSubscriber_I *subscriber) override;
  
  /**
   * @brief 
   * 
   * @param gpio 
   */
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
