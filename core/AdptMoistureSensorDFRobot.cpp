#include "AdptMoistureSensorDFRobot.hpp"

#include <cstring>
#include <exception>

float MOISTURE_WATER = 1425;
float MOISTURE_AIR = 3150;
float MAX_NORM_VALUE = 1000;

AdptMoistureSensorDFRobot::AdptMoistureSensorDFRobot(std::shared_ptr<IAdptMoistureSensorDFRobot> moistureSensor)
    : m_MoistureSensor(moistureSensor)
{
    if(!m_MoistureSensor)
    {
        throw std::invalid_argument("moistureSensor is not set");
    }
}

std::optional<float> AdptMoistureSensorDFRobot::getValue() const
{
    auto actualValue = (std::optional<float>)m_MoistureSensor->readValue();

    if (actualValue.has_value())
    {
        actualValue = -((actualValue.value() - MOISTURE_WATER) / ((MOISTURE_AIR - MOISTURE_WATER) / MAX_NORM_VALUE) - MAX_NORM_VALUE);
    }

    return actualValue;
}

const sensor_t AdptMoistureSensorDFRobot::getInfo() const
{
    sensor_t sensor_info;

    char name[12] = "MS-DFRobot";

    memcpy(sensor_info.name, name, strlen(name));
    sensor_info.sensor_id = 0;
    sensor_info.type = SENSOR_TYPE_SOIL_MOISTURE;
    sensor_info.max_value = MAX_NORM_VALUE;
    sensor_info.min_value = 0;
    sensor_info.min_delay = 0;
    sensor_info.resolution = MAX_NORM_VALUE;
    sensor_info.version = 1;

    return sensor_info;
}

void AdptMoistureSensorDFRobot::init()
{
    m_MoistureSensor->init();
}
