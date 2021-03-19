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
  bool success = false;
  pwmState = DISABLED;
  dutyCycle = 0;
  frequency = 0;
  intensity = 0;
  success = true;
  return success;
}

void PwmController::startEventLoop(bool &terminate)
{

}

void PwmController::enable()
{

}

void PwmController::disable()
{

}

void PwmController::operator!()
{
  pwmState = DISABLED;
}

void PwmController::operator++()
{
  if(intensity < 100) 
  { 
    ++intensity; 
  }
}

void PwmController::operator+=(const uint8_t value)
{
  if(intensity + value <= 100) 
  { 
    intensity += value; 
  }
}

void PwmController::operator--()
{
  if(intensity > 0)
  {
    --intensity;
  }
}

void PwmController::operator-=(const uint8_t value)
{
  if(intensity > 0)
  {
    intensity -= value;
  }
}

void PwmController::setIntensity(const uint8_t value)
{
  if(value <= 100 && value >=0)
  {
    intensity = value;
  }
}

uint8_t PwmController::getIntensity() const
{
  return intensity;
}

void PwmController::setFrequency(const uint32_t value)
{
  if(value < FREQUENCY_MAX && value > FREQUENCY_MIN)
  {
    frequency = value;
  }
}

uint32_t PwmController::getFrequency() const
{
  return frequency;
}

void PwmController::setDutyCycle(const uint8_t value)
{
  if(value < DUTY_CYCLE_MAX && value > DUTY_CYCLE_MIN)
  {
    dutyCycle = value;
  }
}

uint8_t PwmController::getDutyCycle() const
{
  return dutyCycle;
}

