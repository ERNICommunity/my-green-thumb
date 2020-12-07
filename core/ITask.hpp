#pragma once

#include <cstdint>
#include <functional>
#include <string>

typedef std::function<void()> taskFunction_t;

typedef struct{
    uint32_t id;
    std::string name;
    uint32_t interval_ms;
    taskFunction_t func;
} task_t;

class ITask
{
public:
    ITask() {};
    virtual ~ITask() {};
    ITask(const ITask&) = delete;
    ITask& operator=(const ITask&) = delete;

    // Interface
    virtual bool start() = 0;
    virtual bool stop() = 0;
    virtual void changeInterval(uint32_t interval) = 0;
    virtual task_t getInfo() = 0;
    virtual bool setTaskFunction(const taskFunction_t &func) = 0;
    virtual bool isRunning() = 0;
};