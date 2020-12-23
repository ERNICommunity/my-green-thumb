#pragma once

#include "stm32l4xx_hal.h"

#include "IAdptMoistureSensorDFRobot.hpp"

class MoistureSensorDFRobot : public IAdptMoistureSensorDFRobot
{
public:
    // Constructor(s)
    MoistureSensorDFRobot() : m_AdcHandle(){};
    ~MoistureSensorDFRobot() = default;

    // Base class methods
    void init();
    const std::optional<uint32_t> readValue();

private:
    bool adcInit();
    bool gpioInit();

private:
    ADC_HandleTypeDef m_AdcHandle;
};