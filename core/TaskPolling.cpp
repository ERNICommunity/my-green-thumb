#include "TaskPolling.hpp"

TaskPolling::TaskPolling(uint32_t id, const std::string &name, uint32_t intervall, const taskFunction_t &callbackFunc) :
    m_Id(id),
    m_Name(name),
    m_Interval(intervall),
    m_CallbackFunc(callbackFunc),
    m_IsRunning(false)
{}

bool TaskPolling::start() 
{
    if(m_CallbackFunc != nullptr)
    {
        m_IsRunning = true;
    }
    
    return m_IsRunning;
}

bool TaskPolling::stop() 
{
    m_IsRunning = false;
    return true;
}

void TaskPolling::changeInterval(uint32_t intervall) 
{
    m_Interval = intervall;
}

task_t TaskPolling::getInfo() 
{
    task_t taskContext;

    taskContext.id = m_Id;
    taskContext.name = m_Name;
    taskContext.interval_ms = m_Interval;

    return taskContext;
}

bool TaskPolling::setTaskFunction(const taskFunction_t &func) 
{
    bool retVal = false;

    if(func)
    {
        m_CallbackFunc = func;
        retVal = true;
    }

    return retVal;
}

bool TaskPolling::isRunning() 
{
    return m_IsRunning;
}

void TaskPolling::schedule() 
{
    if(m_IsRunning && (m_CallbackFunc != nullptr))
    {
        m_CallbackFunc();
    }
}
