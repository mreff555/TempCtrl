#ifndef BUTTONSUBSCRIBER_HPP
#define BUTTONSUBSCRIBER_HPP

#include "buttonSubscriber_I.hpp"

class ButtonManager;

class ButtonSubscriber : public ButtonSubscriber_I
{
  public:
  ButtonSubscriber(ButtonManager &publisher);

  virtual ~ButtonSubscriber(){}

  void update(const Button &buttonUpdate) override;

  void subscribe(uint8_t gpio);  

  void unsubscribe(uint8_t gpio);

  private:
  
  // Need to handle multiple.  Get it to compile then fix.
  //Button button;
  ButtonManager &buttonPublisher;
  static int static_number_;
  int number_;

};

#endif /* BUTTONSUBSCRIBER_HPP */
