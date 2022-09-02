#include "pidProcessor.hpp"

PidProcessor::PidProcessor(){}

dwell_t PidProcessor::Process(const temp_t current){}

void PidProcessor::setSetPoint(const temp_t){}

temp_t PidProcessor::getSetPoint() const{}

void PidProcessor::setKp(const temp_t){}

temp_t PidProcessor::getKp() const{}

void PidProcessor::setKi(const temp_t){}

temp_t PidProcessor::getKi() const{}
    
void PidProcessor::setKd(const temp_t){}

temp_t PidProcessor::getKd() const{}

temp_t PidProcessor::getError(const temp_t current){}

temp_t PidProcessor::getProportional(const temp_t error){}

temp_t PidProcessor::getIntegral(const temp_t error){}

temp_t PidProcessor::getDerivative(const temp_t error){}

dwell_t PidProcessor::getDwellXferFunc(
    const temp_t pTemp,
    const temp_t iTemp,
    const temp_t dTemp){}