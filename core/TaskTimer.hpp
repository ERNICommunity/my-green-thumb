#pragma once

#include <memory>

#include "ITask.hpp"
#include "ITimer.hpp"

class TaskTimer : public ITask
{
public:
    TaskTimer(uint32_t id, const std::string &name, uint32_t interval_ms, std::unique_ptr<ITimer> timer, taskFunction_t callbackFunc=nullptr);
    virtual ~TaskTimer() = default;

    // ITask interface implementation
    bool start();
    bool stop();
    void changeInterval(uint32_t intervall);
    task_t getInfo();
    bool setTaskFunction(const taskFunction_t &func);
    bool isRunning();

private:
    int32_t m_Id;
    std::string m_Name;

    std::unique_ptr<ITimer> m_Timer;
};
