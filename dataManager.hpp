#ifndef DATAMANAGER_HPP
#define DATAMANAGER_HPP
#include "buttonSubscriber_I.hpp"
#include "lcdScreen.hpp"
#include "common.hpp"
#include "button.hpp"
#include <list>
#include <string>
#include <vector>

class ButtonManager;

class DataManager : public ButtonSubscriber_I
{
public:
  DataManager(
    ButtonManager &_buttonManager, 
    LcdScreen &_lcdScreen);

  ~DataManager();
  
  void startEventLoop(bool &terminate);
  
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

  void sendTempToLcd(std::string tempstr);

private:
  ButtonManager &buttonManager;  

  LcdScreen &mLcdScreen;

  std::list<TempStruct> mTempStructList;

  TScale_E mTempScale;

  InputMode_E mInputMode;

  std::string currentTempString;

  float setPoint;
  
  std::vector<Button> registeredButton;
};

#endif /* DATAMANAGER_HPP */
