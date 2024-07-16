/**
* @brief This file contains Navigation entry point
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/
#include "include/sensor_fusion.h"
#include "pi/headers/aggregate_types_laser_scan.h"
#include "pi/headers/aggregate_types_odometry.h"

namespace {
static agv::sensor_fusion::Sensor_Fusion* g_sensor_fusion = nullptr;
}

/// <summary>
///  @brief initialization
/// </summary>
void PI_Sensor_Fusion_I(const PI_Odometry_Pose& pose_in,
                        const PI_Laser_Scan& scanner_in,
                        const PI_Floor_Targets& floor_targets_in,
                        PI_Odometry_Pose& fused_pose_out) {
  static agv::sensor_fusion::Sensor_Fusion sensor_fusion_module(
      pose_in, scanner_in, floor_targets_in, fused_pose_out);
  g_sensor_fusion = &sensor_fusion_module;
}

/// <summary>
///  @brief step function
/// </summary>
void PI_Sensor_Fusion_S(
    [[maybe_unused]] const PI_Odometry_Pose& pose_in,
    [[maybe_unused]] const PI_Laser_Scan& scanner_in,
    [[maybe_unused]] const PI_Floor_Targets& floor_targets_in,
    [[maybe_unused]] PI_Odometry_Pose& fused_pose_out) {
  g_sensor_fusion->run();
}

namespace agv::sensor_fusion {
/// <summary>
///  @brief public entry point for the class object invoked by
///         the PD container
/// </summary>
void Sensor_Fusion::run() {
  state_machine();
}

/// <summary>
///  @brief state machine of sensor_fusion thats runs periodic
/// </summary>
void Sensor_Fusion::state_machine() {
  g_sensor_fusion->predict();
  g_sensor_fusion->update();
}
}  // namespace agv::sensor_fusion