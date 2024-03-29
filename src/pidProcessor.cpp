#include <pidProcessor.hpp>

PidProcessor::PidProcessor()
    : parameterLimits(TEMP_MAX_SP, TEMP_MIN_SP, TEMP_SP_DEFAULT)
{
  printf("Initializing PID Controller: %s\n", init() ? "PASS" : "FAIL");
}

bool PidProcessor::init()
{
  //TODO: ...
  return true;
}

dwell_t PidProcessor::Process(const temp_t current) {}

void PidProcessor::setSetPoint(const temp_t input)
{
  this->setPoint = parameterLimits.validate(input);
}

temp_t PidProcessor::getSetPoint() const { return this->setPoint; }

void PidProcessor::setKp(const temp_t input)
{
  this->kp = parameterLimits.validate(input);
}

temp_t PidProcessor::getKp() const { return this->kp; }

void PidProcessor::setKi(const temp_t input)
{
  this->ki = parameterLimits.validate(input);
}

temp_t PidProcessor::getKi() const { return this->ki; }

void PidProcessor::setKd(const temp_t input)
{
  this->kd = parameterLimits.validate(input);
}

temp_t PidProcessor::getKd() const { return this->kd; }

temp_t PidProcessor::getError(const temp_t current)
{
  return this->currentError;
}

temp_t PidProcessor::getProportional(const temp_t error)
{
  temp_t returnValue = this->kp;
}

temp_t PidProcessor::getIntegral(const temp_t error) {}

temp_t PidProcessor::getDerivative(const temp_t error) {}

dwell_t PidProcessor::getDwellXferFunc(const temp_t pTemp, const temp_t iTemp,
                                       const temp_t dTemp)
{
}