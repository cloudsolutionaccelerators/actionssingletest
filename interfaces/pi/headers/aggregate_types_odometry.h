/**
* @brief This file contains all odometry interface types
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __INTERFACES_PI_HEADERS_AGGREGATE_TYPES_ODOMETRY_H__
#define __INTERFACES_PI_HEADERS_AGGREGATE_TYPES_ODOMETRY_H__

#include <cstdint>

/// <summary>
/// Pose Data Structure
/// </summary>
typedef struct PI_Odometry_Pose_ {
  using float32_t = float;

  /// This could either be corrected or uncorrected pose
  /// data structure and depends on where the data is
  /// coming from. When its coming from sensor fusion
  /// its corrected, otherwise uncorrected.
  float32_t x;
  float32_t y;
  float32_t heading;

} PI_Odometry_Pose;

/// <summary>
/// @brief Wheel sensor data structure
/// </summary>
typedef struct PI_Wheel_Sensor_ {
  using float32_t = float;

  /// <summary>
  /// @brief
  /// This is the information from wheel sensors
  /// Some adaptation will be needed to account
  /// for the various units that are typically
  /// used like RPM, Rad/s, Duty cycle which will
  /// be accomplished using input/output adapters.
  /// Steering angle could be degree or radians.
  /// The code will assume the RPM and radian.
  /// Adaptation layer will handle conversions
  /// for the simulation and target vehicle.
  /// <summary>

  /// @brief in RPM
  float32_t rotation_speed;

  /// @brief in radian
  float32_t steering_angle;

} PI_Wheel_Sensor;

#define PI_NUMBER_OF_WHEEL_ENCODERS (4)

/// <summary>
/// Wheel encoder data structure
/// </summary>
typedef struct PI_Wheel_Encoder_ {

  PI_Wheel_Sensor data[PI_NUMBER_OF_WHEEL_ENCODERS];

} PI_Wheel_Encoder;

#endif