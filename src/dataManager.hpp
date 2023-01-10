#ifndef DATAMANAGER_HPP
#define DATAMANAGER_HPP
#include "button.hpp"
#include "buttonSubscriber_I.hpp"
#include "common.hpp"
#include "lcdScreen.hpp"
#include <list>
#include <memory>
#include <string>
#include <vector>

class ButtonManager;

class DataManager : public ButtonSubscriber_I
{
public:
  DataManager(std::shared_ptr<ButtonManager> _buttonManager,
              std::shared_ptr<LcdScreen> _lcdScreen);

  ~DataManager();

  void startEventLoop(bool &terminate);

  void update(const Button &buttonUpdate) override;

  void subscribe(uint8_t gpio);

  void unsubscribe(uint8_t gpio);

  bool init();

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

  float getSetPoint() const;

  void setSetPoint(const float setPoint);

private:
  std::shared_ptr<ButtonManager> mButtonManager;

  std::shared_ptr<LcdScreen> mLcdScreen;

  std::list<TempStruct> mTempStructList;

  TScale_E mTempScale;

  InputMode_E mInputMode;

  float setPoint;

  std::vector<Button> registeredButton;
};

#endif /* DATAMANAGER_HPP */
