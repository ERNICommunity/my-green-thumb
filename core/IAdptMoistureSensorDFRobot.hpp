#pragma once

#include <optional>

class IAdptMoistureSensorDFRobot
{
public:
  // Constructor(s)
  IAdptMoistureSensorDFRobot() = default;
  virtual ~IAdptMoistureSensorDFRobot() = default;

  virtual const std::optional<uint32_t> readValue() = 0;
  virtual const bool init() = 0;
};