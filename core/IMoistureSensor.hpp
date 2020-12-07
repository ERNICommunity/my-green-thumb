#pragma once

#include "Sensor.hpp"

class IMoistureSensor : public Sensor
{
public:
  // Constructor(s)
  IMoistureSensor() = default;
  virtual ~IMoistureSensor() = default;
};