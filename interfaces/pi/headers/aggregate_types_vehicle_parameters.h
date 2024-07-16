/**
* @brief This file contains all parameters interface types
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __INTERFACES_PI_HEADERS_AGGREGATE_TYPES_VEHICLE_PARAMETERS_H__
#define __INTERFACES_PI_HEADERS_AGGREGATE_TYPES_VEHICLE_PARAMETERS_H__

#include <cstdint>

/// <summary>
/// @brief Indicates the drive system
/// </summary>
#define PI_REARWHEEL_DRIVE (0)
#define PI_FRONTWHEEL_DRIVE (1)
#define PI_ALLWHEEL_DRIVE (2)

/// <summary>
/// Wheel parameter data structure
/// </summary>
typedef struct PI_Wheel_Parameters_ {
  using float32_t = float;

  // in meters
  float32_t wheel_diameter;

  // distance between front and rear axle
  // in meters
  float32_t wheelbase;

  // 0 = Rearwheel drive
  // 1 = Frontwheel drive
  // 2 = AWD
  uint8_t drive_system;

} PI_Wheel_Parameters;

/// <summary>
/// Vehicle parameter data structure
/// </summary>
typedef struct PI_Vehicle_Parameters_ {
  PI_Wheel_Parameters wheel;
} PI_Vehicle_Parameters;

#endif