#include "dataManager.hpp"
#include "buttonManager.hpp"
#include <cstdint>
#include <thread>
#include <iostream>

/*********************************************
* Class: DataManager                         *
*                                            *
* Description:                               *
* The purpose of this class is to provide a  *
* centralized location for storing input     *
* data.                                      *
**********************************************/
DataManager::DataManager(
  ButtonManager &_buttonManager, 
  LcdScreen &_lcdScreen) 
: mButtonManager(_buttonManager), 
mLcdScreen(_lcdScreen)
{
  printf("Initializing Data Manager: %s\n", 
    init() ? "PASS" : "FAIL");
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

void DataManager::startEventLoop(
  bool &terminate)
{
  float previousTemp = 0;
  if(mTempStructList.back().temp)
  {
    mLcdScreen.sendTemp(
      mTempStructList.back().temp, mTempScale);
  }
  else
  {
    mLcdScreen.sendTemp(888, mTempScale);
  }

  std::vector<Button> lastState(
    registeredButton);
  while(terminate == false)
  {
    /*****************************************
    * The conditions in this for loop make   *
    * up the general behavior of the         *
    * buttons. One-off behavior can be       *
    * implemented elsewhere.                 *
    *****************************************/
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
        if(registeredButton[i].getGpio() == 27) 
        {
          registeredButton[i] << lastState[i];
          switch(mInputMode)
          {
            case SETPOINT:
            {
              // float tempSp = getSetPoint();
              // if (tempSp < TEMP_MAX_SP)
              // {
              //   setSetPoint(tempSp + 0.5);
              // } 
              break;
            }

            case SET_SCALE:
              break;  
            
            case LOAD_PROFILE:
              break;

            case PID_TUNE:
              break;
          }
        }
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

  // This is where buttons are any buttons are registered
  // TODO: I may want to consolidate these actions
  // into a single function.  I guess I'll wait until
  // all of the buttons are working to decide
  //
  /* Menu Button Registration */
  registeredButton.push_back(Button(26));                // Create a button object, gpio 26
  mButtonManager.addButton(registeredButton.back());     // Add the button to the button manager
  subscribe(registeredButton.back().getGpio());          // Subscribe to button updates

  /* Up Button Registration */
  registeredButton.push_back(Button(27));
  mButtonManager.addButton(registeredButton.back());
  subscribe(registeredButton.back().getGpio());

  /* Down Button Registration*/
  registeredButton.push_back(Button(17));
  mButtonManager.addButton(registeredButton.back());
  subscribe(registeredButton.back().getGpio());

  /* Back Button Registration*/
  registeredButton.push_back(Button(19));
  mButtonManager.addButton(registeredButton.back());
  subscribe(registeredButton.back().getGpio());

  
  // If at least one temperature value has been
  // received and recorded set the initial setpoint
  // to that value.  Otherwise use the default
  // value.
  // TODO:  This needs to be watched.  There was an
  // intermitant failure which I did not debug, before
  // the problem "went away" but it appears that calling
  // the size method when the vector is empty generates
  // an error.
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

// TODO: This is ugly with all the casts.  I'd like a 
// more clean way to do it.
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
