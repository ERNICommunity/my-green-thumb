#include "TaskTimer.hpp"

#include <exception>

TaskTimer::TaskTimer(uint32_t id,
                     const std::string &name,
                     uint32_t interval_ms,
                     std::unique_ptr<ITimer> timer,
                     taskFunction_t callbackFunc) : m_Id(id),
                                                    m_Name(name),
                                                    m_Timer(std::move(timer))
{
    if(m_Timer)
    {
        m_Timer->setInterval(interval_ms);
    }
    else
    {
        throw std::invalid_argument("m_Timer is empty");
    }

    if(callbackFunc)
    {
        m_Timer->setCallbackFunc(callbackFunc);
    }

    if (m_Timer->isRunning())
    {
        stop();
    }
}

void TaskTimer::start()
{
    if (!m_Timer->isRunning())
    {
        m_Timer->start();
    }
}

void TaskTimer::stop()
{
    if (m_Timer->isRunning())
    {
        m_Timer->stop();
    }
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

void TaskTimer::setTaskFunction(const taskFunction_t &func)
{
    if (func)
    {
        m_Timer->setCallbackFunc(func);
    }
    else
    {
        throw std::invalid_argument("func is empty");
    }
}

bool TaskTimer::isRunning()
{
    return m_Timer->isRunning();
}