#include "dataManager.hpp"
#include "buttonManager.hpp"
#include <cstdint>

DataManager::DataManager(
  ButtonManager &_buttonManager, 
  LcdScreen &_lcdScreen) 
: buttonManager(_buttonManager), 
mLcdScreen(_lcdScreen)
{
  init();
}

DataManager::~DataManager()
{
  auto it = registeredButton.begin();
  while(it != registeredButton.end())
  {
    unsubscribe(it->getGpio());
    ++it;
  }

}

void DataManager::update(const Button &buttonUpdate)
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

void DataManager::subscribe(uint8_t gpio)
{
  this->buttonManager.attach(gpio, this); 
}

void DataManager::unsubscribe(uint8_t gpio = 0)
{
  this->buttonManager.detach(gpio, this);
}

void DataManager::init()
{

}

void DataManager::shutdown()
{

}

TempStruct DataManager::getCurrentTempStruct() const
{
  return mTempStructList.back();
}

void DataManager::setCurrentTempStruct(const TempStruct tempStruct)
{
  if(mTempStructList.size() >= TEMP_HISTORY_SIZE)
  {
    mTempStructList.pop_front();
  }

  mTempStructList.push_back(tempStruct);
}

std::list<TempStruct> DataManager::getTempStructHistory() const
{
  //TODO: return by reference
  return mTempStructList;
}

TScale_E DataManager::getTempScale() const
{
  return mTempScale;
}

void DataManager::setTempScale(const TScale_E tScale)
{
  mTempScale = tScale;
}

void DataManager::nextTempScale()
{
  int temp;
  temp = (int)mTempScale + 1;
  if(temp >= (int)MAX_VALUE_TSCALE) { temp = 0; }
  mTempScale = (TScale_E)temp;
}

InputMode_E DataManager::getInputMode() const
{
  return mInputMode;  
}

void DataManager::setInputMode(const InputMode_E inputMode)
{
  mInputMode = inputMode;
}

void DataManager::nextInputMode()
{
  int temp;
  temp = (int)mInputMode + 1;
  if(temp >= (int)INPUT_MODE_MAX_VALUE) { temp = 0; }
  mInputMode = (InputMode_E)temp;
}

void DataManager::sendTempToLcd(std::string tempstr)
{
  mLcdScreen.sendActualTemp(tempstr.c_str());
}
