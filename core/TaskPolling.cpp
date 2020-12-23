#include "TaskPolling.hpp"

#include <exception>

TaskPolling::TaskPolling(uint32_t id, const std::string &name, uint32_t intervall, const taskFunction_t &callbackFunc) :
    m_Id(id),
    m_Name(name),
    m_Interval(intervall),
    m_CallbackFunc(callbackFunc),
    m_IsRunning(false)
{
    if(!m_CallbackFunc)
    {
        throw std::invalid_argument("func is empty");
    }
}

void TaskPolling::start() 
{
    m_IsRunning = true;
}

void TaskPolling::stop() 
{
    m_IsRunning = false;
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

void TaskPolling::setTaskFunction(const taskFunction_t &func) 
{
    if(func)
    {
        m_CallbackFunc = func;
    }
    else
    {
        throw std::invalid_argument("func is empty");
    }
}

bool TaskPolling::isRunning() 
{
    return m_IsRunning;
}

void TaskPolling::schedule() 
{
    if(m_IsRunning)
    {
        m_CallbackFunc();
    }
}
