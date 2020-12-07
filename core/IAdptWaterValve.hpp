#pragma once

class IAdptWaterValve
{
public:
    IAdptWaterValve() = default;
    virtual ~IAdptWaterValve() = default;

    virtual bool init() = 0;
    virtual void open() = 0;
    virtual void close() = 0;
};