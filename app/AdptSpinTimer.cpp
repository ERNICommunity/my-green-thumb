#include "AdptSpinTimer.hpp"

#include <cassert>

AdptSpinTimer::AdptSpinTimer(timerInterval_t interval_ms) : m_Interval_ms(interval_ms), m_MyTimerAction(), m_Timer(&m_MyTimerAction, true, interval_ms)
{
    if (m_Timer.isRunning())
    {
        stop();
    }
}

bool AdptSpinTimer::start()
{
    m_Timer.startTimer(m_Interval_ms);
    return true;
}

bool AdptSpinTimer::stop()
{
    m_Timer.cancelTimer();
    return true;
}

bool AdptSpinTimer::isRunning()
{
    return m_Timer.isRunning();
}

bool AdptSpinTimer::setCallbackFunc(const timerCallbackFunc_t &func)
{
    bool retVal = false;
    if (func)
    {
        m_MyTimerAction.setTaskFunction(func);
        retVal = true;
    }
    return retVal;
}

bool AdptSpinTimer::setInterval(timerInterval_t interval_ms)
{
    if (m_Interval_ms != interval_ms)
    {
        m_Interval_ms = interval_ms;

        if (m_Timer.isRunning())
        {
            m_Timer.cancelTimer();
            m_Timer.startTimer(m_Interval_ms);
        }
    }

    return true;
}

timerInterval_t AdptSpinTimer::getInterval() const
{
    return m_Interval_ms;
}

bool MyTimerAction::setTaskFunction(const timerCallbackFunc_t &func)
{
    bool retVal = false;

    if (func)
    {
        m_CallbackFunc = func;
        retVal = true;
    }

    return retVal;
}

void MyTimerAction::timeExpired()
{
    assert(m_CallbackFunc);
    m_CallbackFunc();
}