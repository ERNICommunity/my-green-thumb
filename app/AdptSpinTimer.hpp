#pragma once

#include "ITimer.hpp"
#include "Timer.h"

class MyTimerAction : public TimerAdapter
{
public:
    MyTimerAction(const timerCallbackFunc_t &callbackFunc = {}) : m_CallbackFunc(callbackFunc){};
    ~MyTimerAction() = default;

    bool setTaskFunction(const timerCallbackFunc_t &func);

    // TimerAdapter interface implementation
    void timeExpired();

private:
    timerCallbackFunc_t m_CallbackFunc;
};

class AdptSpinTimer : public ITimer
{
private:
    timerInterval_t m_Interval_ms;
    MyTimerAction m_MyTimerAction;
    Timer m_Timer;

public:
    AdptSpinTimer(timerInterval_t interval_ms = 10);
    ~AdptSpinTimer() = default;

    // ITimer interface implementation
    bool start();
    bool stop();
    bool isRunning();
    bool setCallbackFunc(const timerCallbackFunc_t &func);
    bool setInterval(timerInterval_t interval_ms);
    timerInterval_t getInterval() const;
};