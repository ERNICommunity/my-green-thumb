#include "TaskTimer.hpp"

#include <cassert>

TaskTimer::TaskTimer(uint32_t id,
                     const std::string &name,
                     uint32_t interval_ms,
                     std::unique_ptr<ITimer> timer,
                     taskFunction_t callbackFunc) : m_Id(id),
                                                    m_Name(name),
                                                    m_Timer(std::move(timer))
{
    assert(m_Timer);
    m_Timer->setInterval(interval_ms);

    if (callbackFunc)
    {
        m_Timer->setCallbackFunc(callbackFunc);
    }
    else
    {
        m_Timer->setCallbackFunc([](void) { assert(0); });
    }

    if (m_Timer->isRunning())
    {
        stop();
    }
}

bool TaskTimer::start()
{
    if (!m_Timer->isRunning())
    {
        m_Timer->start();
    }
    return true;
}

bool TaskTimer::stop()
{
    if (m_Timer->isRunning())
    {
        m_Timer->stop();
    }
    return true;
}

void TaskTimer::changeInterval(uint32_t interval_ms)
{
    m_Timer->setInterval(interval_ms);
}

task_t TaskTimer::getInfo()
{
    task_t taskContext;

    taskContext.id = m_Id;
    taskContext.name = m_Name;
    taskContext.interval_ms = m_Timer->getInterval();

    return taskContext;
}

bool TaskTimer::setTaskFunction(const taskFunction_t &func)
{
    bool retVal = false;
    if (func)
    {
        m_Timer->setCallbackFunc(func);
        retVal = true;
    }
    return retVal;
}

bool TaskTimer::isRunning()
{
    return m_Timer->isRunning();
}