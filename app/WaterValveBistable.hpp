#pragma once

#include <memory>

#include "IAdptWaterValve.hpp"
#include "ITimer.hpp"

class WaterValveBistable : public IAdptWaterValve
{
private:
    std::unique_ptr<ITimer> m_Timer;

public:
    WaterValveBistable(std::unique_ptr<ITimer> timer) : m_Timer(std::move(timer))
    {
        // Configure Timer
        m_Timer->setCallbackFunc(std::bind(&WaterValveBistable::resetOutputs, this));
    };
    ~WaterValveBistable() = default;

    // Interface implementation
    bool init();
    void open();
    void close();

private:
    void resetOutputs();
};