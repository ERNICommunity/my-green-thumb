#pragma once

#include "IAdptWaterValveBistable.hpp"
#include "ITimer.hpp"

class WaterValveBistable : public IAdptWaterValveBistable
{
public:
    WaterValveBistable() = default;
    virtual ~WaterValveBistable() = default;

    // Interface implementation
    void init();
    void open();
    void close();
    void reset();
    uint32_t getImpulseDuration() const;
};