#pragma once

class IValve
{
public:
    IValve() = default;
    virtual ~IValve() = default;
    IValve(const IValve&) = delete;
    IValve& operator=(const IValve&) = delete;

    virtual const bool init() = 0;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual bool isOpen() const = 0;
};