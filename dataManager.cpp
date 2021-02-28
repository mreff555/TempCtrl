#include "dataManager.hpp"
#include "buttonManager.hpp"
#include <cstdint>
#include <thread>
#include <iostream>

DataManager::DataManager(
  ButtonManager &_buttonManager, 
  LcdScreen &_lcdScreen) 
: mButtonManager(_buttonManager), 
mLcdScreen(_lcdScreen)
{
  printf("Initializing Data Manager: %s\n", init() ? "PASS" : "FAIL");
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

void DataManager::startEventLoop(bool &terminate)
{
  float previousTemp = 0;
  mLcdScreen.sendTemp(mTempStructList.back().temp, mTempScale);
  std::vector<Button> lastState(registeredButton);
  while(terminate == false)
  {
    /***************************************************/
    /* The conditions in this for loop make up the     */
    /* general behavior of the buttons.  One-off       */
    /* behavior can be implemented elsewhere.          */
    /***************************************************/
    for(int i = 0; i < registeredButton.size(); ++i)
    {
      if(lastState[i].getState() != LONG_HOLD 
        && difftime(registeredButton[i].getTimeStamp(), 
          lastState[i].getTimeStamp()) > 0.5
        && registeredButton[i].getState() == FALLING_EDGE)
      {
        /* Menu button */
        if(registeredButton[i].getGpio() == 26)
        {
          registeredButton[i] << lastState[i];
          nextInputMode();
        }
        /* Up button */
        if(0 /* registeredButton[i].getGpio() == ?? */) {}
        /* Down button */
        if(0 /* registeredButton[i].getGpio() == ?? */) {}
        /* Back button */
        if(0 /* registeredButton[i].getGpio() == ?? */) {}
      }
    }
  
    if(previousTemp != mTempStructList.back().temp)
    {
      mLcdScreen.sendTemp(mTempStructList.back().temp, mTempScale);
      previousTemp = mTempStructList.back().temp;
    }  
    std::this_thread::sleep_for(std::chrono::milliseconds(SCAN_RATE));
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
  this->mButtonManager.attach(gpio, this); 
}

void DataManager::unsubscribe(uint8_t gpio = 0)
{
  this->mButtonManager.detach(gpio, this);
}

bool DataManager::init()
{
  bool success = false;
  registeredButton.push_back(Button(26));  // Menu button
  mButtonManager.addButton(registeredButton.back());
  subscribe(registeredButton.back().getGpio());
  if(mTempStructList.size() > 0)
  {
    setPoint = mTempStructList.back().temp;
  }
  else
  {
    setPoint = TEMP_SP_DEFAULT;
  }
  setTempScale(DEFAULT_TEMP_SCALE);
  return setPoint ? true : false;
}

void DataManager::shutdown()
{
  auto it = registeredButton.begin();
  while(it != registeredButton.end())
  {
    unsubscribe(it->getGpio());
    ++it;
  }
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
  mLcdScreen.sendNewMode(mInputMode, setPoint, mTempScale);
  std::cout << "InputMOde: " << (int)mInputMode << "\n";
}

float DataManager::getSetPoint() const
{
  return setPoint;  
}

void DataManager::setSetPoint(const float sp)
{
  setPoint = sp;
}
