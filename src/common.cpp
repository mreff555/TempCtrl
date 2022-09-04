#include "common.hpp"

temp_t ParameterLimits::validate(const temp_t input)
{
    temp_t returnValue = this->defaultValue;
    if(input <= this->max && input >= this->min)
        returnValue = input;
    return returnValue;
}
