/**
* @brief This file contains all laser scan interface types
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __INTERFACES_PI_HEADERS_AGGREGATE_TYPES_LASER_SCAN_H__
#define __INTERFACES_PI_HEADERS_AGGREGATE_TYPES_LASER_SCAN_H__

#include <cstdint>

// The maximum number of reflections allowed during one laser scanner revolution
#define PI_MAX_REFLECTIONS_PER_REV (40)

/// Represents a potential match of reflection and target
typedef struct PI_Target_Data_ {
  using float32_t = float;

  /// System coordinates of target in meters
  /// and radians
  float32_t target_x;
  float32_t target_y;
  float32_t target_heading;

} PI_Target_Data;

// Reflection structure
typedef struct PI_Laser_Scan_ {

  /// The timestamp of the data
  uint32_t time_stamp_in_ms;

  uint8_t number_of_reflections;
  PI_Target_Data data[PI_MAX_REFLECTIONS_PER_REV];

} PI_Laser_Scan;

#endif