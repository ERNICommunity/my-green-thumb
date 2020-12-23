#include "AdptSpinTimer.hpp"

#include <exception>

AdptSpinTimer::AdptSpinTimer(timerInterval_t interval_ms) : m_Interval_ms(interval_ms),
                                                            m_MyTimerAction(),
                                                            m_Timer(interval_ms, &m_MyTimerAction, SpinTimer::IS_RECURRING, SpinTimer::IS_NON_AUTOSTART)
{}

void AdptSpinTimer::start()
{
    m_Timer.start(m_Interval_ms);
}

void AdptSpinTimer::stop()
{
    m_Timer.cancel();
}

bool AdptSpinTimer::isRunning()
{
    return m_Timer.isRunning();
}

void AdptSpinTimer::setCallbackFunc(const timerCallbackFunc_t &func)
{
    if (func)
    {
        m_MyTimerAction.setTaskFunction(func);
    }
    else
    {
        throw std::invalid_argument("Function is empty");
    }
}

void AdptSpinTimer::setInterval(const timerInterval_t interval_ms)
{
    if (m_Interval_ms != interval_ms)
    {
        m_Interval_ms = interval_ms;

        if (m_Timer.isRunning())
        {
            m_Timer.cancel();
            m_Timer.start(m_Interval_ms);
        }
    }
}

timerInterval_t AdptSpinTimer::getInterval() const
{
    return m_Interval_ms;
}

void MyTimerAction::setTaskFunction(const timerCallbackFunc_t &func)
{
    if (func)
    {
        m_CallbackFunc = func;
    }
    else
    {
        throw std::invalid_argument("Function is empty");
    }
}

void MyTimerAction::timeExpired()
{
    if (m_CallbackFunc)
    {
        m_CallbackFunc();
    }
    else
    {
        throw std::logic_error("m_CallbackFunc is not set");
    }
}