#include "Service.hpp"

#include <exception>

std::atomic<uint32_t> Service::idCount = 1;

Service::Service(std::unique_ptr<ITask> task) : m_Id(idCount), m_Task(std::move(task))
{
    idCount++;

    if (m_Task)
    {
        m_Task->setTaskFunction(std::bind(&Service::doWork, this));
    }
    else
    {
        throw std::invalid_argument("Task pointer is NULL");
    }
}

void Service::start()
{
    setup();
    m_Task->start();
}

void Service::stop()
{
    m_Task->stop();
    dispose();
}

bool Service::isRunning() const
{
    return m_Task->isRunning();
}

void Service::setInterval(uint32_t interval_ms)
{
    m_Task->changeInterval(interval_ms);
}

uint32_t Service::getId() const
{
    return m_Id;
}