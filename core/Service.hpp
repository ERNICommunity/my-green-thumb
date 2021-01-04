#pragma once

#include <atomic>
#include <memory>
#include "ITask.hpp"

class Service
{
public:
    // Constructor
    Service(std::unique_ptr<ITask> task);
    virtual ~Service() = default;

public:
    void start();
    void stop();
    bool isRunning() const;
    void setInterval(uint32_t interval_ms);
    uint32_t getId() const;

protected:
    // Interface methods
    virtual void setup() = 0;
    virtual void dispose() = 0;
    virtual void doWork() = 0;

private:
    static std::atomic<uint32_t> idCount;
    uint32_t m_Id;
    std::unique_ptr<ITask> m_Task;
};