#include "thermocoupleReceiver.hpp"
#include "dataManager.hpp"
#include "common.hpp"
#include <cstdint>
#include <fstream>
#include <errno.h>
#include <string>
#include <thread>

ThermocoupleReceiver::ThermocoupleReceiver(DataManager &_dataManager) : mDataManager(_dataManager) 
{
  printf("Initializing Thermocouple Receiver: %s\n", init() ? "PASS" : "FAIL");
  // setTempScale(DEFAULT_TEMP_SCALE);
}

ThermocoupleReceiver::~ThermocoupleReceiver()
{

}

uint8_t ThermocoupleReceiver::init()
{
  uint8_t slaveCount = 0;
  std::fstream SLA_CNT_FS(W1_SLAVE_COUNT, std::ios_base::in);
  if(SLA_CNT_FS.is_open())
  {
    uint8_t slaves = static_cast<uint8_t>(SLA_CNT_FS.peek());
    if(slaves > 0)
    {
      std::fstream SLA_FS(W1_SLAVES, std::ios_base::in);
      if(SLA_FS.is_open())
      {
        std::string line; 
        while(getline(SLA_FS, line))
        {
          slavesArr.push_back(line);
          if(SLA_FS.bad())
          {
            perror("Bad! ");
          }
          else if(SLA_FS.eof())
          {
            break;
          }
        }
        SLA_FS.close();
      }
      else
      {
        perror("Failed to retrieve slave ID ");
      }
    }
    SLA_CNT_FS.close();
  }
  else
  {
    perror("Failed to retrieve slave count ");
  }
  return slavesArr.size();
}

void ThermocoupleReceiver::startEventLoop(bool &terminate)
{
  getTemp(0);
  while(terminate == false)
  {
    getTemp(0);
    std::this_thread::sleep_for(std::chrono::milliseconds(SCAN_RATE));
  }
}

/***********************************************
*  Fetches the current time from the specified *
*  temperature controller, and stores the      *
*  returned value with time stamp and device   *
*  id, in the tempStruct array.    
************************************************/
void ThermocoupleReceiver::getTemp(int idx)
{
  std::string fpath(W1_DEV_ROOT);
  fpath += slavesArr[idx];
  fpath += "/w1_slave";
  std::fstream fs(fpath, std::ios_base::in);
  fs.seekg(0, fs.end);
  size_t size = fs.tellg();
  fs.seekg(0, fs.beg);
  char buffer[size];
  fs.read(buffer, size);
  std::string tempStr(buffer);
  float value = std::stof(
    tempStr.substr(
      tempStr.find("t=",0,2) + 2, 
      tempStr.find_last_of('\0')
    )) / 1000;
  TempStruct ts;
  ts.temp = value;
  ts.id = slavesArr[idx];
  ts.ts = time(NULL);
  mDataManager.setCurrentTempStruct(ts);
}
