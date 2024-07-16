/**
* @brief This file contains 30ms periodic task
*        update call.
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#include "pd/headers/pd_data_types.h"
#include "pd/headers/pd_wrappers.h"

namespace pd::guidance {
pd::wrappers::Std_ReturnType Read_Move_Cmd_From_Host(
    [[maybe_unused]] pd::agv::Move_Cmd& cmd) {
  // implement the low level read from the host
  // and copy the data into cmd. If failure then
  // set the appropriate error code to the return
  // type.
  return pd::wrappers::Std_ReturnType::READ_OK;
}
pd::wrappers::Std_ReturnType Read_Moves_From_Config(
    [[maybe_unused]] pd::agv::Moves& moves) {
  // implement the low level read from the config
  // and copy the data into move. If failure then
  // set the appropriate error code to the return
  // type.
  return pd::wrappers::Std_ReturnType::READ_OK;
}
pd::wrappers::Std_ReturnType Read_Pose_From_Sensor_Fusion(
    [[maybe_unused]] pd::agv::Odometry_Pose& moves) {
  // implement the low level read from the config
  // and copy the data into move. If failure then
  // set the appropriate error code to the return
  // type.
  return pd::wrappers::Std_ReturnType::READ_OK;
}
pd::wrappers::Std_ReturnType Read_Status_From_Supervisor(
    [[maybe_unused]] pd::agv::Supervisor_Status& cmd) {
  // implement the low level read from the config
  // and copy the data into move. If failure then
  // set the appropriate error code to the return
  // type.
  return pd::wrappers::Std_ReturnType::READ_OK;
}
pd::wrappers::Std_ReturnType Read_Floor_Targets_From_Config(
    [[maybe_unused]] pd::agv::Floor_Targets& targets) {
  // implement the low level read from the parameter file
  // and copy the data into cmd. If failure then
  // set the appropriate error code to the return
  // type.
  return pd::wrappers::Std_ReturnType::READ_OK;
}
pd::wrappers::Std_ReturnType Read_Nodes_From_Config(
    [[maybe_unused]] pd::agv::Floor_Nodes& cmd) {
  // implement the low level read from the config
  // and copy the data into move. If failure then
  // set the appropriate error code to the return
  // type.
  return pd::wrappers::Std_ReturnType::READ_OK;
}
pd::wrappers::Std_ReturnType Read_Motion_Cmd_From_Motion_Control(
    [[maybe_unused]] pd::agv::Wheel_Encoder& cmd) {
  // implement the low level read from the motion cmd
  // and copy the data into cmd. If failure then
  // set the appropriate error code to the return
  // type.
  return pd::wrappers::Std_ReturnType::READ_OK;
}
pd::wrappers::Std_ReturnType Read_Laser_Scan_From_IO(
    [[maybe_unused]] pd::agv::Laser_Scan& scan) {
  // implement the low level read from the motion cmd
  // and copy the data into cmd. If failure then
  // set the appropriate error code to the return
  // type.
  return pd::wrappers::Std_ReturnType::READ_OK;
}
pd::wrappers::Std_ReturnType Read_Vehicle_Parameters_From_Config(
    [[maybe_unused]] pd::agv::Vehicle_Parameters& params) {
  // implement the low level read from the parameter file
  // and copy the data into cmd. If failure then
  // set the appropriate error code to the return
  // type.
  return pd::wrappers::Std_ReturnType::READ_OK;
}
pd::wrappers::Std_ReturnType Write_Cmd_To_Motion_Control(
    [[maybe_unused]] pd::agv::Wheel_Encoder& cmd) {
  // implement the low level read from the config
  // and copy the data into move. If failure then
  // set the appropriate error code to the return
  // type.
  return pd::wrappers::Std_ReturnType::READ_OK;
}
}  // namespace pd::guidance

namespace {

using namespace pd::agv;
Odometry_Pose fused_pose_in;
Supervisor_Status supervisor_in;
Floor_Targets floor_targets_in;
Floor_Nodes floor_nodes_in;
Moves moves_in;
Move_Cmd move_cmd_in;
Wheel_Encoder motion_cmd_in;
Laser_Scan laser_scan_in;
Vehicle_Parameters vehicle_parameters_in;
Wheel_Encoder guidance_cmd_out;

bool task_30ms_init_done = false;

void __attribute__((unused)) task_30ms_periodic(void) {

  if (!task_30ms_init_done) {
    Guidance_I();
    task_30ms_init_done = true;
  }

  Guidance_S();
}
}  // namespace