#pragma once

#include <memory>
#include <exception>

#include "Service.hpp"
#include "WaterRegulator.hpp"

class ServiceWaterRegulator : public Service
{
private:
    std::shared_ptr<WaterRegulator> m_WaterRegulator;

public:
    ServiceWaterRegulator(std::unique_ptr<ITask> task,
                          std::shared_ptr<WaterRegulator> service) : Service(std::move(task)),
                                                                     m_WaterRegulator(service)
    {
        if(not m_WaterRegulator)
        {
            throw std::invalid_argument("service is not set");
        }
    };
    virtual ~ServiceWaterRegulator() = default;

private:
    // Service Interface
    void setup()
    {
        m_WaterRegulator->setup();
    };

    void dispose()
    {
        m_WaterRegulator->dispose();
    };

    void doWork()
    {
        m_WaterRegulator->regulateMoisture();
    };
};