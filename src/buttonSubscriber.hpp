#ifndef BUTTONSUBSCRIBER_HPP
#define BUTTONSUBSCRIBER_HPP

#include <button.hpp>
#include <buttonSubscriber_I.hpp>
#include <cstdint>
#include <memory>
#include <vector>

class ButtonManager;

class ButtonSubscriber : public ButtonSubscriber_I
{
public:
  ButtonSubscriber(std::shared_ptr<ButtonManager>(_buttonManager));

  virtual ~ButtonSubscriber();

  void update(const Button &buttonUpdate) override;

  void subscribe(uint8_t gpio);

  void unsubscribe(uint8_t gpio);

private:
  std::shared_ptr<ButtonManager> buttonManager;

  // protected:
public:
  std::vector<Button> registeredButton;
};

#endif /* BUTTONSUBSCRIBER_HPP */
