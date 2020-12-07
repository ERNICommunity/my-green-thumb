#include "WaterRegulator.hpp"

uint32_t THOLD_DRY = 200;
uint32_t THOLD_WET = 850;
// uint32_t m_RegIntervalValveOpen_ms = 10000;
// uint32_t m_RegIntervalValveClose_ms = 250;

bool WaterRegulator::setup()
{
    if (!m_MoistureSensor->init())
    {
        return false;
    }

    if (!m_WaterValve->init())
    {
        return false;
    }
    m_WaterValve->close();

    return true;
}

void WaterRegulator::regulateMoisture()
{
    auto actualMoisture = m_MoistureSensor->getValue();

    if ((actualMoisture < THOLD_DRY) && !m_WaterValve->isOpen())
    {
        m_WaterValve->open();
        // TODO: increase intervall
    }
    else if ((actualMoisture > THOLD_WET) && m_WaterValve->isOpen())
    {
        m_WaterValve->close();
        // TODO: decrease intervall
    }
    else if ((actualMoisture > THOLD_DRY) && (actualMoisture < THOLD_WET))
    {
        // Do nothing
    }
}

bool WaterRegulator::dispose()
{
    return true;
}
