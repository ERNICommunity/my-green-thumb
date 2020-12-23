#pragma once

#include <inttypes.h>

class IAdptWaterValveBistable
{
public:
    IAdptWaterValveBistable() = default;
    virtual ~IAdptWaterValveBistable() = default;

    virtual void init() = 0;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void reset() = 0;
    virtual uint32_t getImpulseDuration() const = 0; //ms
};