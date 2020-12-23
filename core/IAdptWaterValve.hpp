#pragma once

class IAdptWaterValve
{
public:
    IAdptWaterValve() = default;
    virtual ~IAdptWaterValve() = default;

    virtual void init() = 0;
    virtual void open() = 0;
    virtual void close() = 0;
};