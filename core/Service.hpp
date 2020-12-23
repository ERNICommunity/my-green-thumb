#pragma once

#include <memory>
#include <exception>

#include "ITask.hpp"

class Service
{
public:
    // Constructor
    Service(std::unique_ptr<ITask> task) : m_Task(std::move(task))
    {
        if(m_Task)
        {
            m_Task->setTaskFunction(std::bind(&Service::doWork, this));
        }
        else
        {
            throw std::invalid_argument("Task pointer is NULL");         
        }
    };
    virtual ~Service(){};

public:
    void start()
    {
        setup();
        m_Task->start();
    };
    void stop()
    {
        m_Task->stop();
        dispose();
    };
    bool isRunning()
    {
        return m_Task->isRunning();
    };

    void setInterval(uint32_t interval_ms)
    {
        m_Task->changeInterval(interval_ms);
    };

protected:
    // Interface methods
    virtual void setup() = 0;
    virtual void dispose() = 0;
    virtual void doWork() = 0;

private:
    std::unique_ptr<ITask> m_Task;
};