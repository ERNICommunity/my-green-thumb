#pragma once

#include "ITask.hpp"

class TaskPolling : public ITask
{
private:
    int32_t m_Id;
    std::string m_Name;
    uint32_t m_Interval;
    taskFunction_t m_CallbackFunc;
    bool m_IsRunning;

public:
    TaskPolling(uint32_t id, const std::string &name, uint32_t intervall, const taskFunction_t &callbackFunc);
    virtual ~TaskPolling() = default;

    // ITask base methods
    void start();
    void stop();
    void changeInterval(uint32_t intervall);
    task_t getInfo();
    void setTaskFunction(const taskFunction_t &func);
    bool isRunning();

    // Specific methods
    // Has to be called periodically
    void schedule();
};
