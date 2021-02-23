#include "tempctrl.hpp"
#include <fstream>
#include <errno.h>
#include <string>
#include <thread>
#include <cstdio> // Debug purposes only

TempCtrl::TempCtrl(void) 
: mLcdScreen(std::unique_ptr<LcdScreen>(new LcdScreen))//,
// mButtonManager(std::unique_ptr<ButtonManager>(new ButtonManager))
{
  // Sets up a file descriptor to screen scrape the w1 thermocouple
  // This may be temporary, as it is inheriently slow
  tempInit();
  
  // Need I say more. 
  setTempScale(DEFAULT_TEMP_SCALE);

  // Button button1(26);
}

TempCtrl::~TempCtrl(void)
{

}

void TempCtrl::startEventLoop(bool &terminate)
{
  while(terminate == false)
  {
    static float previousTemp = tempStruct.back().temp;
    getTemp(0);
    if(previousTemp != tempStruct.back().temp)
    printTemp(tempScaleVal);
    std::this_thread::sleep_for(std::chrono::milliseconds(SCAN_RATE));
  }
}

uint8_t TempCtrl::tempInit(void)
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

void TempCtrl::getTemp(int idx)
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
  tempStruct.push_back(ts);
}

void TempCtrl::setTempScale(TScale_E scale)
{
  if(scale > -1 && scale < MAX_VALUE_TSCALE)
    tempScaleVal = scale;  

}

void TempCtrl::wait(size_t seconds)
{
  clock_t clockPerMS = CLOCKS_PER_SEC / 1000;
  clock_t end;
  end = clock() + seconds * clockPerMS;
  while(clock() < end) {}
}

void TempCtrl::printTemp(enum TScale_E scale = CELSIUS)
{
  std::string strbuf;
  switch (scale)
  {
    case CELSIUS:
      strbuf += std::to_string(tempStruct.back().temp);
      strbuf.erase(strbuf.find('.',0) + 4);
      strbuf += "C";
      break;
    case FARENHEIT:
      strbuf += std::to_string(32.000 + tempStruct.back().temp * 9.000 / 5.000);
      strbuf.erase(strbuf.find('.',0) + 4);
      strbuf += "F";
      break;
    case KELVIN:
      strbuf += std::to_string(tempStruct.back().temp + 273.150);
      strbuf.erase(strbuf.find('.',0) + 4);
      strbuf += "K";
      break;
    case RANKINE:
      strbuf += std::to_string((tempStruct.back().temp + 273.150) * 9.000 / 5.000);
      strbuf.erase(strbuf.find('.',0) + 4);
      strbuf += "R";
      break;
  }
  mLcdScreen->sendActualTemp(strbuf.c_str());
}
