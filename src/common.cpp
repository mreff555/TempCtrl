#include "common.hpp"

temp_t ParameterLimits::validate(const temp_t input)
{
  temp_t returnValue = this->defaultValue;
  if (input <= this->max && input >= this->min)
    returnValue = input;
  return returnValue;
}

temp_t ParameterLimits::getMin() const { return this->min; }

temp_t ParameterLimits::getMax() const { return this->max; }

temp_t ParameterLimits::getDefault() const { return this->defaultValue; }
