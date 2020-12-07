#pragma once

#include <memory>
#include <cassert>

#include "Service.hpp"
#include "WaterRegulator.hpp"

class ServiceWaterRegulator : public Service
{
private:
    std::shared_ptr<WaterRegulator> m_WaterRegulator;

public:
    ServiceWaterRegulator(std::shared_ptr<ITask> task,
                          std::shared_ptr<WaterRegulator> service) : Service(task),
                                                                     m_WaterRegulator(service)
    {
        assert(m_WaterRegulator);
    };
    virtual ~ServiceWaterRegulator() = default;

private:
    // Service Interface
    bool setup()
    {
        return m_WaterRegulator->setup();
    };

    bool dispose()
    {
        return m_WaterRegulator->dispose();
    };

    void doWork()
    {
        m_WaterRegulator->regulateMoisture();
    };
};