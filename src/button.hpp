/**
 * @file button.hpp
 * @author Dan Feerst (feerstd@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <common.hpp>
#include <cstdint>
#include <ctime>
#include <string>

class Button
{
public:
  /**
   * @brief Creates a button object which will monitor
   * the specified GPIO.  There is no error checking for
   * valid GPIO's at the moment.  Partially because I am
   * lazy and partially because it will very from model
   * to model.
   *
   * @param gpio
   */
  Button(uint8_t gpio, std::string buttonDesc = "");

  /**
   * @brief Destroy the Button object
   *
   */
  virtual ~Button() = default;

  /**
   * @brief Update the button state.  Possible values are
   * -  DEFAULT_STATE
   * -  RISING_EDGE
   * -  LONG_HOLD
   * -  FALLING_EDGE
   *
   * @param newValue
   */
  void update(ButtonState newValue);

  /**
   * @brief Return the buttons GPIO value
   *
   * @return uint8_t GPIO
   */
  uint8_t getGpio() const;

  /**
   * @brief Get the State object
   *
   * @return ButtonState
   */
  ButtonState getState() const;

  /**
   * @brief Get the Time Stamp object
   *
   * @return time_t
   */
  time_t getTimeStamp() const;

  /**
   * @brief Get button description
   *
   * @return std::string
   */
  std::string getButtonDesc() const;

  /**
   * @brief If gpio's match, update timestamp and state and
   * return true.  Otherwise return false
   *
   * @param rhs Button
   * @return true GPIO's match.  Timestamp and stat updated.
   * @return false No match.  Nothing updated.
   */
  bool operator<<(const Button &rhs);

private:
  // gpio number which button is acting on
  uint8_t gpioId;

  // current button state
  ButtonState buttonState;

  // last button update
  time_t timeStamp;

  // button description
  std::string mButtonDesc;
  
};

#endif /* BUTTON_HPP */
