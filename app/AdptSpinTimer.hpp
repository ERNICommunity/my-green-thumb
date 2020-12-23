#pragma once

#include "ITimer.hpp"
#include "SpinTimer.h"

class MyTimerAction : public SpinTimerAction
{
public:
    MyTimerAction(const timerCallbackFunc_t &callbackFunc = {}) : m_CallbackFunc(callbackFunc){};
    ~MyTimerAction() = default;

    void setTaskFunction(const timerCallbackFunc_t &func);

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
    SpinTimer m_Timer;

public:
    AdptSpinTimer(timerInterval_t interval_ms = 10);
    ~AdptSpinTimer() = default;

    // ITimer interface implementation
    void start();
    void stop();
    bool isRunning();
    void setCallbackFunc(const timerCallbackFunc_t &func);
    void setInterval(const timerInterval_t interval_ms);
    timerInterval_t getInterval() const;
};