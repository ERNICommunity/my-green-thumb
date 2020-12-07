#pragma once

#include <memory>
#include <cassert>

#include "ITask.hpp"

class Service
{
public:
    // Constructor
    Service(std::shared_ptr<ITask> task) : m_Task(task)
    {
        assert(m_Task);

        if( !m_Task->setTaskFunction(std::bind(&Service::doWork, this)) )
        {
            assert(0);
        }
    };
    virtual ~Service(){};

public:
    bool start()
    {
        if (!setup())
            return false;

        if (!m_Task->start())
            return false;

        return true;
    };
    bool stop()
    {
        if (!m_Task->stop())
            return false;

        if (!dispose())
            return false;

        return true;
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
    virtual bool setup() = 0;
    virtual bool dispose() = 0;
    virtual void doWork() = 0;

private:
    std::shared_ptr<ITask> m_Task;
};