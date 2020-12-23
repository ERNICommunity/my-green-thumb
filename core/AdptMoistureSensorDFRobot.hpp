#pragma once

#include <memory>

#include "IMoistureSensor.hpp"
#include "IAdptMoistureSensorDFRobot.hpp"

class AdptMoistureSensorDFRobot : public IMoistureSensor
{
public:
  // Constructor
  AdptMoistureSensorDFRobot(std::shared_ptr<IAdptMoistureSensorDFRobot> moistureSensor);
  virtual ~AdptMoistureSensorDFRobot() = default;

  // Base class methods
  /*! @brief Get the latest sensor event
      @returns Contains the value if able to fetch an value */
  std::optional<float> getValue() const;
  /*! @brief Get info about the sensor itself */
  const sensor_t getInfo() const;
  /*! @brief Init the sensor itself */
  void init();

private:
  std::shared_ptr<IAdptMoistureSensorDFRobot> m_MoistureSensor;
};