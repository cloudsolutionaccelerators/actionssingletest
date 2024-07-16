
/**
* @brief This file contains all laser scan interface types
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __TESTS_GAZEBO_SIM_GAZEBO_INTERFACE_H__
#define __TESTS_GAZEBO_SIM_GAZEBO_INTERFACE_H__

#include <tuple>
#include <vector>

/// @brief vehicle software outputs
typedef struct Gazebo_In_Data_ {
  bool alarm_activated;
  bool light_activated;

  // commands from agv
  std::vector<double> steering_angle;
  std::vector<double> motor_speed;

  // fork position
  double fork_pos;

  // vehicle pose
  std::tuple<double, double, double> pose;

} Gazebo_In_Data;

/// @brief sensor data structure
typedef struct Gazebo_Out_Data_ {

  // gazebo sensor data
  std::vector<std::tuple<double, double, double>> scan_data;
  bool estop_activated;

  // sensor readings
  std::vector<double> steering_angle;
  std::vector<double> motor_speed;

  // fork position
  double fork_pos;
} Gazebo_Out_Data;

#endif