#include "tempdatamanager.hpp"
#include "buttonManager.hpp"
#include <cstdint>

TempDataManager::TempDataManager(ButtonManager &_buttonManager) 
: buttonManager(_buttonManager)
{
  init();
}

TempDataManager::~TempDataManager()
{
  auto it = registeredButton.begin();
  while(it != registeredButton.end())
  {
    unsubscribe(it->getGpio());
    ++it;
  }

}

void TempDataManager::update(const Button &buttonUpdate)
{
  auto it = registeredButton.begin();
  while(it != registeredButton.end())
  {
    // The button << overload copies data for matching button ID's only.
    // This isn't 100% intuitive, but I'm going to do it anyway.
    (*it) << buttonUpdate;
    ++it;
  }
}

void TempDataManager::subscribe(uint8_t gpio)
{
  this->buttonManager.attach(gpio, this); 
}

void TempDataManager::unsubscribe(uint8_t gpio = 0)
{
  this->buttonManager.detach(gpio, this);
}

void TempDataManager::init()
{

}

void TempDataManager::shutdown()
{

}

TempStruct TempDataManager::getCurrentTempStruct() const
{
  return mTempStructList.back();
}

void TempDataManager::setCurrentTempStruct(const TempStruct tempStruct)
{
  if(mTempStructList.size() >= TEMP_HISTORY_SIZE)
  {
    mTempStructList.pop_front();
  }

  mTempStructList.push_back(tempStruct);
}

std::list<TempStruct> TempDataManager::getTempStructHistory() const
{
  //TODO: return by reference
  return mTempStructList;
}

TScale_E TempDataManager::getTempScale() const
{
  return mTempScale;
}

void TempDataManager::setTempScale(const TScale_E tScale)
{
  mTempScale = tScale;
}

void TempDataManager::nextTempScale()
{
  int temp;
  temp = (int)mTempScale + 1;
  if(temp >= (int)MAX_VALUE_TSCALE) { temp = 0; }
  mTempScale = (TScale_E)temp;
}

InputMode_E TempDataManager::getInputMode() const
{
  return mInputMode;  
}

void TempDataManager::setInputMode(const InputMode_E inputMode)
{
  mInputMode = inputMode;
}

void TempDataManager::nextInputMode()
{
  int temp;
  temp = (int)mInputMode + 1;
  if(temp >= (int)INPUT_MODE_MAX_VALUE) { temp = 0; }
  mInputMode = (InputMode_E)temp;
}
