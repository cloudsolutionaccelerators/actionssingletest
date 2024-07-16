/**
* @brief This file defines all the apis needed to
*        read/write the firmware and other data
*        communicated from the hosts etc.
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __PD_HEADERS_DATA_HANDLERS_H__
#define __PD_HEADERS_DATA_HANDLERS_H__

#include "pd/headers/pd_data_types.h"
#include "pd/headers/pd_wrappers.h"

namespace pd::guidance {
typename pd::wrappers::Std_ReturnType Read_Move_Cmd_From_Host(
    pd::agv::Move_Cmd& cmd);
typename pd::wrappers::Std_ReturnType Read_Moves_From_Config(
    pd::agv::Moves& cmd);
typename pd::wrappers::Std_ReturnType Read_Floor_Targets_From_Config(
    pd::agv::Floor_Targets& cmd);
typename pd::wrappers::Std_ReturnType Read_Pose_From_Sensor_Fusion(
    pd::agv::Odometry_Pose& pose);
typename pd::wrappers::Std_ReturnType Read_Status_From_Supervisor(
    pd::agv::Supervisor_Status& faults);
typename pd::wrappers::Std_ReturnType Read_Nodes_From_Config(
    pd::agv::Floor_Nodes& nodes);
typename pd::wrappers::Std_ReturnType Read_Motion_Cmd_From_Motion_Control(
    pd::agv::Wheel_Encoder& cmd);
typename pd::wrappers::Std_ReturnType Read_Laser_Scan_From_IO(
    pd::agv::Laser_Scan& scan);
typename pd::wrappers::Std_ReturnType Read_Vehicle_Parameters_From_Config(
    pd::agv::Vehicle_Parameters& scan);
typename pd::wrappers::Std_ReturnType Write_Cmd_To_Motion_Control(
    pd::agv::Wheel_Encoder& cmd);
}  // namespace pd::guidance
#endif