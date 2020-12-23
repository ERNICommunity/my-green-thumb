#pragma once

#include <memory>
#include "IMoistureSensor.hpp"
#include "IValve.hpp"

class WaterRegulator
{
private:
    std::shared_ptr<IMoistureSensor> m_MoistureSensor;
    std::shared_ptr<IValve> m_WaterValve;

public:
    WaterRegulator(std::shared_ptr<IMoistureSensor> moistureSensor,
                   std::shared_ptr<IValve> waterValve);
    virtual ~WaterRegulator() = default;
    WaterRegulator(const WaterRegulator&) = delete;
    WaterRegulator& operator=(const WaterRegulator&) = delete;

    void setup();
    void regulateMoisture();
    void dispose();
};
