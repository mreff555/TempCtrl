#ifndef TEMPDATAMANAGER_HPP
#define TEMPDATAMANAGER_HPP
#include "buttonSubscriber_I.hpp"
#include "common.hpp"
#include "button.hpp"
#include <list>
#include <vector>

class ButtonManager;

class TempDataManager : public ButtonSubscriber_I
{
public:
  TempDataManager(ButtonManager &_buttonManager);

  ~TempDataManager();
  
  void update(const Button &buttonUpdate) override;

  void subscribe(uint8_t gpio);  

  void unsubscribe(uint8_t gpio);

  void init();

  void shutdown();

  TempStruct getCurrentTempStruct() const;

  void setCurrentTempStruct(const TempStruct tempStruct);

  std::list<TempStruct> getTempStructHistory() const;
  
  TScale_E getTempScale() const;

  void setTempScale(const TScale_E tScale);

  void nextTempScale();

  InputMode_E getInputMode() const;

  void setInputMode(const InputMode_E inputMode);

  void nextInputMode();

private:
  ButtonManager &buttonManager;  

  std::list<TempStruct> mTempStructList;

  TScale_E mTempScale;

  InputMode_E mInputMode;

//protected:
  public:
  std::vector<Button> registeredButton;
};

#endif /* TEMPDATAMANAGER_HPP */
