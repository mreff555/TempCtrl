#include "pwmController.hpp"
#include <cstdio>
#include <sys/mman.h>
#include <fcntl.h>

PwmController::PwmController()
{
  printf("Initializing PWM Controller: %s\n", init() ? "PASS" : "FAIL");
}

PwmController::~PwmController()
{

}

bool PwmController::init()
{
  uint8_t structSizeResult = validateStructMemorySize();
  bool memAccess = false;
  if(
    structSizeResult > 0 
    &&(fd = open("/dev/mem", O_RDWR | O_SYNC | O_CLOEXEC)) >= 0)
  {
    pwm_base = (uint32_t *)mmap(
      0,
      0x1000, //0x28,
      PROT_READ | PROT_WRITE,
      MAP_SHARED,
      fd,
      PWM0_BASE);
    memAccess = true;
  }
  data = (PwmStruct*)&pwm_base; 
  // DEBUG
  uint32_t test = (uint32_t&)pwm_base;
  printf("Control: %x %x\n", test, *pwm_base);
  printf("MSEN2: %d %d\n", data->ctl.MSEN2, (0x0001 & (*pwm_base) >> 15));
  printf("USEF2: %d %d\n", data->ctl.USEF2, (0x0001 & (*pwm_base) >> 13));
  printf("POLA2: %d\n", data->ctl.POLA2);
  printf("SBIT2: %d\n", data->ctl.SBIT2);
  printf("RPTL2: %d\n", data->ctl.RPTL2);
  printf("MODE2: %d\n", data->ctl.MODE2);
  
  return structSizeResult && memAccess;
}

void PwmController::startEventLoop(bool &terminate)
{

}

uint8_t PwmController::validateStructMemorySize()
{
  uint8_t sum = 0; 
  bool fail = false;
  
  fail = ((sizeof(data->ctl) == 4) ? false : true);
  if(fail) { sum = 0; }
  else{ sum += sizeof(data->ctl); }

  fail = ((sizeof(data->sta) == 4) ? false : true);
  if(fail) { sum = 0; }
  else{ sum += sizeof(data->sta); }

  fail = ((sizeof(data->dmac) == 4) ? false : true);
  if(fail) { sum = 0; }
  else{ sum += sizeof(data->dmac); }

  fail = ((sizeof(data->rangeData) == 20) ? false : true);
  if(fail) { sum = 0; }
  else{ sum += sizeof(data->rangeData); }
  return sum;
}
