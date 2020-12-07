#pragma once

#include <functional>

typedef uint32_t timerInterval_t;
typedef std::function<void()> timerCallbackFunc_t;

class ITimer
{
public:
    ITimer() = default;
    virtual ~ITimer() = default;
    ITimer(const ITimer&) = delete;
    ITimer& operator=(const ITimer&) = delete;

    virtual bool start() = 0;
    virtual bool stop() = 0;
    virtual bool isRunning() = 0;
    virtual bool setCallbackFunc(const timerCallbackFunc_t &) = 0;
    virtual bool setInterval(timerInterval_t) = 0;
    virtual timerInterval_t getInterval() const = 0;
};
