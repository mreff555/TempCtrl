/**
 * @file pidProcessor.hpp
 * @author Dan Feerst (feerstd@gmail.com)
 * @brief A PID processor for driving a heating coil with
 * millisecond dwell time
 * @version 0.1
 * @date 2022-09-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PID_PROCESSOR_HPP
#define PID_PROCESSOR_HPP
#include "common.hpp"
#include <cstdint>
#include <chrono>

/**
 * @brief Pid Processor - A PID processor for driving a heating coil with
 * millisecond dwell time
 * 
 */
class PidProcessor
{
    /**
     * @brief Construct a new Pid Processor object
     * 
     */
    PidProcessor();

    /**
     * @brief Delete copy constructor
     * 
     */
    PidProcessor(const PidProcessor&) = delete;

    /**
     * @brief Delete copy assignment operator
     * 
     * @return PidProcessor& 
     */
    PidProcessor &operator = (const PidProcessor&) = delete;

    /**
     * @brief Destroy the Pid Processor object
     * 
     */
    virtual ~PidProcessor() = default;

    /**
     * @brief 
     * 
     * @param current 
     * @return dwell_t 
     */
    dwell_t Process(const temp_t current);

    /**
     * @brief Initilize PID loop
     * 
     * @return true success
     * @return false fail
     */
    bool init();

    /**
     * @brief Set the process temperature set point in degrees ºC
     * Min/Max: 
     */
    void setSetPoint(const temp_t);

    /**
     * @brief Get the process temperature set point
     * 
     * @return temp_t 
     */
    temp_t getSetPoint() const;

    /**
     * @brief Set the proportional gain
     * Min/Max:
     * 
     */
    void setKp(const temp_t);

    /**
     * @brief Get the proportional gain
     * 
     * @return temp_t 
     */
    temp_t getKp() const;

    /**
     * @brief Set the integral gain
     * Min/Max:
     * 
     */
    void setKi(const temp_t);

    /**
     * @brief Get the integral gain
     * 
     * @return temp_t 
     */
    temp_t getKi() const;
    
    /**
     * @brief Set the derivative gain
     * Min/Max:
     * 
     */
    void setKd(const temp_t);

    /**
     * @brief Get the derivative gain
     * 
     * @return temp_t 
     */
    temp_t getKd() const;

    private:

    /**
     * @brief The set point is the desired process value.  The pid
     * will attempt to reach this value as fast as possible a minimal
     * overshoot.  Achieving this relies on properly tuened PID K-values
     * and a transfer function that works well for the application
     * 
     */
    temp_t setPoint;

    /**
     * @brief Proportional gain
     * Min / Max: 20ºC / 100ºC
     * 
     */
    temp_t kp;

    /**
     * @brief Integral gain
     * Min / Max: 20ºC / 100ºC
     */
    temp_t ki;

    /**
     * @brief Derivative gain
     * Min / Max: 20ºC / 100ºC
     * 
     */
    temp_t kd;

    /**
     * @brief Current temperature deviation from the set point
     * 
     */
    temp_t currentError;

    /**
     * @brief Setpoint limits
     * 
     */
    ParameterLimits parameterLimits;

    /**
     * @brief Get temperature error
     * 
     * @param current - current temperature T2
     * @return temp_t - temperature error e(t)
     */
    temp_t getError(const temp_t current);

    /**
     * @brief Get the proportional adjustment
     * 
     * @param error - temperature error e(t)
     * @return temp_t - Proportional temperature adjustment 
     */
    temp_t getProportional(const temp_t error);

    /**
     * @brief Get the integral adjustment
     * 
     * @param error - temperature error e(t)
     * @return temp_t - Integral temperature adjustment
     */
    temp_t getIntegral(const temp_t error);

    /**
     * @brief Get the Derivative object
     * 
     * @param error - temperature error e(t)
     * @return temp_t - Derivative temperature adjustment
     */
    temp_t getDerivative(const temp_t error);

    /**
     * @brief Get the transfer function result
     * 
     * @param pTemp - Proportional adjustment
     * @param iTemp - Integral adjustment
     * @param dTemp - Derivative adjustment
     * @return dwell_t 
     */
    dwell_t getDwellXferFunc(
        const temp_t pTemp,
        const temp_t iTemp,
        const temp_t dTemp);
};

#endif /* PID_PROCESSOR_HPP */
