#include "AdptWaterValveBistable.hpp"

#include <exception>

AdptWaterValveBistable::AdptWaterValveBistable(std::shared_ptr<IAdptWaterValveBistable> waterValve, std::unique_ptr<ITimer> timer) : m_WaterValve(waterValve),
                                                                                                             m_IsOpen(true),
                                                                                                             m_Timer(std::move(timer))
{
    if(m_Timer)
    {
        m_Timer->setCallbackFunc(std::bind(&AdptWaterValveBistable::resetValve, this));
    }
    else
    {
        throw std::invalid_argument("m_Timer is empty");
    } 
    
    if(!m_WaterValve)
    {
        throw std::invalid_argument("m_WaterValve is empty");
    }

    close();
}

AdptWaterValveBistable::~AdptWaterValveBistable() 
{
    m_WaterValve->close();
}

void AdptWaterValveBistable::init()
{
    m_Timer->setInterval(m_WaterValve->getImpulseDuration());

    m_WaterValve->init();
}

void AdptWaterValveBistable::open()
{
    if (!m_IsOpen)
    {
        m_WaterValve->open();
        m_IsOpen = true;
        m_Timer->start();
    }
}

void AdptWaterValveBistable::close()
{
    if (m_IsOpen)
    {
        m_WaterValve->close();
        m_IsOpen = false;
        m_Timer->start(); 
    }
}

bool AdptWaterValveBistable::isOpen() const
{
    return m_IsOpen;
}

void AdptWaterValveBistable::resetValve() 
{
    m_WaterValve->reset();
    m_Timer->stop();
}