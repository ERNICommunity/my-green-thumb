#pragma once

#include <memory>
#include "IValve.hpp"
#include "IAdptWaterValve.hpp"

class AdptWaterValve : public IValve
{
private:
    std::shared_ptr<IAdptWaterValve> m_WaterValve;
    bool m_IsOpen;

public:
    AdptWaterValve(std::shared_ptr<IAdptWaterValve> waterValve) : m_WaterValve(waterValve), m_IsOpen(true)
    {
        m_WaterValve->close();
    };

    ~AdptWaterValve()
    {
        m_WaterValve->close();
    };

    void init()
    {
        m_WaterValve->init();
    }

    void open()
    {
        if (!m_IsOpen)
        {
            m_WaterValve->open();
            m_IsOpen = true;
        }
    };

    void close()
    {
        if (m_IsOpen)
        {
            m_WaterValve->close();
            m_IsOpen = false;
        }
    };

    bool isOpen() const
    {
        return m_IsOpen;
    };
};
