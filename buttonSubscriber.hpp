#ifndef BUTTONSUBSCRIBER_HPP
#define BUTTONSUBSCRIBER_HPP

#include "buttonSubscriber_I.hpp"
#include "button.hpp"
#include <vector>

class ButtonManager;

class ButtonSubscriber : public ButtonSubscriber_I
{
  public:
  ButtonSubscriber(ButtonManager &_buttonManager);

  virtual ~ButtonSubscriber();

  void update(const Button &buttonUpdate) override;

  void subscribe(uint8_t gpio);  

  void unsubscribe(uint8_t gpio);

  private:
  
  ButtonManager &buttonManager;
 
  // This vector does nothing yet.  I think I am going to have to iterate
  // through a list of buttons, but need need the cleanest way of doing so 
  std::vector<Button> localButtonList;
  Button menuButton;
  // Button backButton;
  // Button upButton;
  // Button downButton;

  // static int static_number_;
  // int number_;

};

#endif /* BUTTONSUBSCRIBER_HPP */
