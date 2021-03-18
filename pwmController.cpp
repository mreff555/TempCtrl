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

}

void PwmController::operator++()
{

}

void PwmController::operator+=(const uint8_t value)
{

}

void PwmController::operator--()
{

}

void PwmController::operator-=(const uint8_t value)
{

}

void PwmController::setIntensity(const uint8_t value)
{

}

uint8_t PwmController::getIntensity() const
{
  return 0;
}

void PwmController::setFrequency(const uint32_t value)
{

}

uint32_t PwmController::getFrequency() const
{
  return 0;
}

void PwmController::setDutyCycle(const uint8_t value)
{

}

uint8_t PwmController::getDutyCycle() const
{
  return 0;
}

