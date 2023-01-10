#include "pwmController.hpp"
#include <cstdio>
#include <fcntl.h>
#include <sys/mman.h>

PwmController::PwmController()
{
  printf("Initializing PWM Controller: %s\n", init() ? "PASS" : "FAIL");
}

PwmController::~PwmController() {}

bool PwmController::init()
{
  bool success = false;
  if (!softPwmCreate(PWM_PIN0, PWM_INITIAL_VALUE, PWM_PIN0_RANGE))
  {
    pwmState = DISABLED;
    dutyCycle = 0;
    frequency = 0;
    intensity = 0;
    softPwmWrite(PWM_PIN0, intensity);
    success = true;
  }
  return success;
}

void PwmController::startEventLoop(bool &terminate) {}

void PwmController::enable() {}

void PwmController::disable() {}

void PwmController::operator!() { pwmState = DISABLED; }

void PwmController::operator++()
{
  if (intensity < 100)
  {
    ++intensity;
    softPwmWrite(PWM_PIN0, intensity);
  }
}

void PwmController::operator+=(const uint8_t value)
{
  if (intensity + value <= 100)
  {
    intensity += value;
    softPwmWrite(PWM_PIN0, intensity);
  }
}

void PwmController::operator--()
{
  if (intensity > 0)
  {
    --intensity;
    softPwmWrite(PWM_PIN0, intensity);
  }
}

void PwmController::operator-=(const uint8_t value)
{
  if (intensity > 0)
  {
    intensity -= value;
    softPwmWrite(PWM_PIN0, intensity);
  }
}

void PwmController::setIntensity(const uint8_t value)
{
  if (value <= 100 && value >= 0)
  {
    intensity = value;
    softPwmWrite(PWM_PIN0, intensity);
  }
}

uint8_t PwmController::getIntensity() const { return intensity; }

void PwmController::setFrequency(const uint32_t value)
{
  if (value < FREQUENCY_MAX && value > FREQUENCY_MIN)
  {
    frequency = value;
  }
}

uint32_t PwmController::getFrequency() const { return frequency; }

void PwmController::setDutyCycle(const uint8_t value)
{
  if (value < DUTY_CYCLE_MAX && value > DUTY_CYCLE_MIN)
  {
    dutyCycle = value;
  }
}

uint8_t PwmController::getDutyCycle() const { return dutyCycle; }
