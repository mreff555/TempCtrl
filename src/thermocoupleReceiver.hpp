#ifndef THERMOCOUPLE_RECEIVER_HPP
#define THERMOCOUPLE_RECEIVER_HPP
#include "common.hpp"
#include <vector>

class DataManager;

class ThermocoupleReceiver
{
public:
  ThermocoupleReceiver(DataManager &_dataManager);

  virtual ~ThermocoupleReceiver();

  void startEventLoop(bool &terminate);

  /***********************************************
   *  Fetches the current time from the specified *
   *  temperature controller, and stores the      *
   *  returned value with time stamp and device   *
   *  id, in the tempStruct array.
   ************************************************/
  void getTemp(int idx = 0);

private:
  uint8_t init();

  DataManager &mDataManager;

  std::vector<std::string> slavesArr;

  int fd;
};

#endif /* THERMOCOUPLE_RECEIVER_HPP */
