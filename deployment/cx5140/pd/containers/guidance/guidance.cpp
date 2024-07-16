/**
* @brief This file contains deployment container
*        for guidance
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#include "adapters/include/guidance.h"
#include "pd/headers/pd_data_handlers.h"
#include "pd/headers/pd_data_types.h"
#include "pd/headers/pd_wrappers.h"
#include "pi/headers/aggregate_types_guidance.h"
#include "pi/headers/aggregate_types_laser_scan.h"
#include "pi/headers/aggregate_types_odometry.h"
#include "pi/headers/container_guidance.h"

namespace pd::guidance {
uint32_t iteration_id = 0U;

PI_Odometry_Pose fused_pose_in{};
PI_Supervisor_Status supervisor_in{};
PI_Floor_Targets floor_targets_in{};
PI_Floor_Nodes floor_nodes_in{};
PI_Moves moves_in{};
PI_Move_Cmd move_cmd_in{};
PI_Wheel_Encoder motion_cmd_in{};
PI_Laser_Scan laser_scan_in{};
PI_Vehicle_Parameters params_in{};
PI_Wheel_Encoder guidance_cmd_out{};

void pull(PI_Move_Cmd& pi_data) {
  pd::agv::Move_Cmd pd_data = pd::agv::Move_Cmd();
  if (pd::wrappers::readData<pd::agv::Move_Cmd&>(Read_Move_Cmd_From_Host,
                                                 pd_data)) {
    adapters::guidance::convert(pd_data, pi_data);
  } else {
    adapters::guidance::invalidate(pi_data);
  }
}

void pull(PI_Moves& pi_data) {
  pd::agv::Moves pd_data = pd::agv::Moves();
  if (pd::wrappers::readData<pd::agv::Moves&>(Read_Moves_From_Config,
                                              pd_data)) {
    adapters::guidance::convert(pd_data, pi_data);
  } else {
    /// There is no invalidate here because this
    /// is only a one time read
  }
}

void pull(PI_Floor_Targets& pi_data) {
  pd::agv::Floor_Targets pd_data = pd::agv::Floor_Targets();
  if (pd::wrappers::readData<pd::agv::Floor_Targets&>(
          Read_Floor_Targets_From_Config, pd_data)) {
    adapters::guidance::convert(pd_data, pi_data);
  }
}

void pull(PI_Odometry_Pose& pi_data) {
  pd::agv::Odometry_Pose pd_data = pd::agv::Odometry_Pose();
  if (pd::wrappers::readData<pd::agv::Odometry_Pose&>(
          Read_Pose_From_Sensor_Fusion, pd_data)) {
    adapters::guidance::convert(pd_data, pi_data);
  } else {
    adapters::guidance::invalidate(pi_data);
  }
}

void pull(PI_Supervisor_Status& pi_data) {
  pd::agv::Supervisor_Status pd_data = pd::agv::Supervisor_Status();
  if (pd::wrappers::readData<pd::agv::Supervisor_Status&>(
          Read_Status_From_Supervisor, pd_data)) {
    adapters::guidance::convert(pd_data, pi_data);
  } else {
    adapters::guidance::invalidate(pi_data);
  }
}

void pull(PI_Floor_Nodes& pi_data) {
  pd::agv::Floor_Nodes pd_data = pd::agv::Floor_Nodes();
  if (pd::wrappers::readData<pd::agv::Floor_Nodes&>(Read_Nodes_From_Config,
                                                    pd_data)) {
    adapters::guidance::convert(pd_data, pi_data);
  } else {
    /// There is no invalidate here because this
    /// is only a one time read
  }
}

void pull(PI_Wheel_Encoder& pi_data) {
  pd::agv::Wheel_Encoder pd_data = pd::agv::Wheel_Encoder();
  if (pd::wrappers::readData<pd::agv::Wheel_Encoder&>(
          Read_Motion_Cmd_From_Motion_Control, pd_data)) {
    adapters::guidance::convert(pd_data, pi_data);
  } else {
    adapters::guidance::invalidate(pi_data);
  }
}

void pull(PI_Laser_Scan& pi_data) {
  pd::agv::Laser_Scan pd_data = pd::agv::Laser_Scan();
  if (pd::wrappers::readData<pd::agv::Laser_Scan&>(Read_Laser_Scan_From_IO,
                                                   pd_data)) {
    adapters::guidance::convert(pd_data, pi_data);
  } else {
    adapters::guidance::invalidate(pi_data);
  }
}

void pull(PI_Vehicle_Parameters& pi_data) {
  pd::agv::Vehicle_Parameters pd_data = pd::agv::Vehicle_Parameters();
  if (pd::wrappers::readData<pd::agv::Vehicle_Parameters&>(
          Read_Vehicle_Parameters_From_Config, pd_data)) {
    adapters::guidance::convert(pd_data, pi_data);
  }
}

void push(PI_Wheel_Encoder& pi_data) {
  pd::agv::Wheel_Encoder pd_data = pd::agv::Wheel_Encoder();
  adapters::guidance::convert(pi_data, pd_data);
  pd::wrappers::writeData<pd::agv::Wheel_Encoder&>(Write_Cmd_To_Motion_Control,
                                                   pd_data);
}
}  // namespace pd::guidance

using namespace pd::guidance;

/// <summary>
/// Init for guidance
/// </summary>
void Guidance_I(void) {
  PI_Guidance_I(fused_pose_in, supervisor_in, floor_targets_in, floor_nodes_in,
                moves_in, move_cmd_in, motion_cmd_in, laser_scan_in, params_in,
                guidance_cmd_out);
}

/// <summary>
/// 30ms periodic update
/// </summary>
void Guidance_S(void) {
  pull(fused_pose_in);
  pull(supervisor_in);
  pull(floor_targets_in);
  pull(floor_nodes_in);
  pull(moves_in);
  pull(move_cmd_in);
  pull(motion_cmd_in);
  pull(laser_scan_in);
  pull(params_in);
  PI_Guidance_S(fused_pose_in, supervisor_in, floor_targets_in, floor_nodes_in,
                moves_in, move_cmd_in, motion_cmd_in, laser_scan_in, params_in,
                guidance_cmd_out);

  push(guidance_cmd_out);
  iteration_id++;
}
