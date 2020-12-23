#pragma once

#include <optional>

/* Constants */

/** Sensor types */
typedef enum
{
  SENSOR_TYPE_SOIL_MOISTURE = (1),
  SENSOR_TYPE_RELATIVE_HUMIDITY = (2),
  SENSOR_TYPE_TEMPERATURE = (3),
  SENSOR_TYPE_VOLTAGE = (4),
  SENSOR_TYPE_CURRENT = (5)
} sensors_type_t;

/* Sensor details (40 bytes) */
/** struct sensor_s is used to describe basic information about a specific
 * sensor. */
typedef struct
{
  char name[12];     /**< sensor name */
  int32_t version;   /**< version of the hardware + driver */
  int32_t sensor_id; /**< unique sensor identifier */
  sensors_type_t type;      /**< this sensor's type (ex. SENSOR_TYPE_LIGHT) */
  float max_value;   /**< maximum value of this sensor's value in SI units */
  float min_value;   /**< minimum value of this sensor's value in SI units */
  float resolution;  /**< smallest difference between two values reported by this
                       sensor */
  int32_t min_delay; /**< min delay in microseconds between events. zero = not a
                        constant rate */
} sensor_t;

/** @brief Common sensor interface to unify various sensors.
 * Intentionally modeled after sensors.h in the Adafruit API:
 * https://github.com/adafruit/Adafruit_Sensor
 */
class Sensor
{
public:
  // Constructor(s)
  Sensor() = default;
  virtual ~Sensor() = default;
  Sensor(const Sensor &) = delete;
  Sensor &operator=(const Sensor &) = delete;

  // Methods to implement by the subclass

  /*! @brief Get the latest sensor value
      @returns Contains the value if able to fetch an value */
  virtual std::optional<float> getValue() const = 0;
  /*! @brief Get info about the sensor itself */
  virtual const sensor_t getInfo() const = 0;
  /*! @brief Setup the sensor itself */
  virtual void init() = 0;

  // Base class methods

  void printSensorDetails(void){
      // sensor_t sensor = getInfo();
      // TODO: Print sensor details to console
  };
};