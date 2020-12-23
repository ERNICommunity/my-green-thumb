#include "WaterRegulator.hpp"

#include <exception>

uint32_t THOLD_DRY = 200;
uint32_t THOLD_WET = 850;
// uint32_t m_RegIntervalValveOpen_ms = 10000;
// uint32_t m_RegIntervalValveClose_ms = 250;

WaterRegulator::WaterRegulator(std::shared_ptr<IMoistureSensor> moistureSensor,
                               std::shared_ptr<IValve> waterValve) : m_MoistureSensor(moistureSensor),
                                                                     m_WaterValve(waterValve)
{
    if(!m_MoistureSensor)
    {throw std::invalid_argument("m_MoistureSensor is nullptr");}

    if(!m_WaterValve)
    {throw std::invalid_argument("m_WaterValve is nullptr");}
}

void WaterRegulator::setup()
{
    m_MoistureSensor->init();
    m_WaterValve->init();
    m_WaterValve->close();
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

void WaterRegulator::dispose()
{
    // Nothing to do
}
