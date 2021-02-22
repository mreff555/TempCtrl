#ifndef TEMPCTRL_HPP
#define TEMPCTRL_HPP

#include "common.hpp"
// #include "button.hpp"
#include "lcdscreen.hpp"
// #include "buttonManager.hpp"

#include <cstdlib>
#include <vector>
#include <cstring>
#include <memory>

#define W1_DEV_ROOT "/sys/bus/w1/devices/w1_bus_master1/"
#define W1_SLAVE_COUNT W1_DEV_ROOT "w1_master_slave_count"
#define W1_SLAVES W1_DEV_ROOT "w1_master_slaves"
#define POLL_FREQ 1000

class TempCtrl
{
public:
  TempCtrl();

  virtual ~TempCtrl();

  void startEventLoop(bool &terminate);

  /***********************************************
  *  Fetches the current time from the specified *
  *  temperature controller, and stores the      *
  *  returned value with time stamp and device   *
  *  id, in the tempStruct array.    
  ************************************************/
  void getTemp(int);

  void setTempScale(TScale_E);

  void lcdToggleEnable(int bits);

  void wait(size_t seconds);

  void printTemp(enum TScale_E);

  std::vector<std::string> slavesArr;

  std::vector<TempStruct> tempStruct;

  TScale_E tempScaleVal = CELSIUS;

  int fd;

private:
  void lcdInit();

  uint8_t tempInit(void);

  /***********************************************
  * exclusive access to atomic safe lcdscreen    *
  * manipulation.  Logic is completely decoupled *
  ************************************************/
  std::unique_ptr<LcdScreen> mLcdScreen;

  /***********************************************
  * The responsibility of the button processor   *
  * is to detect edge changes in for specified   *
  * GPIO's, determine the type of press and call *
  * the relavant callback.                       * 
  ************************************************/
  //std::unique_ptr<ButtonManager> mButtonManager;

};
#endif /* TEMPCTRL_HPP */
