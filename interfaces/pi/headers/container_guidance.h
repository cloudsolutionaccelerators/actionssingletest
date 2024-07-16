/**
* @brief This file contains the pi container interface for 
*        guidance component
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __INTERFACES_PI_HEADERS_CONTAINER_GUIDANCE_H__
#define __INTERFACES_PI_HEADERS_CONTAINER_GUIDANCE_H__

#include "pi/headers/aggregate_types_sensor_fusion.h"
#include "pi/headers/aggregate_types_supervisor.h"
#include "pi/headers/aggregate_types_vehicle_parameters.h"

/// <summary>
/// Container interface for guidance component Init
/// </summary>

void PI_Guidance_I(const PI_Odometry_Pose& pose_in,
                   const PI_Supervisor_Status& supervisor_in,
                   const PI_Floor_Targets& floor_targets_in,
                   const PI_Floor_Nodes& floor_nodes_in,
                   const PI_Moves& moves_in, const PI_Move_Cmd& move_cmd_in,
                   const PI_Wheel_Encoder& motion_cmd_in,
                   const PI_Laser_Scan& laser_scan_in,
                   const PI_Vehicle_Parameters& params_in,
                   PI_Wheel_Encoder& motion_cmd_out);

/// <summary>
/// Container interface for guidance component Step
/// </summary>
void PI_Guidance_S(const PI_Odometry_Pose& pose_in,
                   const PI_Supervisor_Status& supervisor_in,
                   const PI_Floor_Targets& floor_targets_in,
                   const PI_Floor_Nodes& floor_nodes_in,
                   const PI_Moves& moves_in, const PI_Move_Cmd& move_cmd_in,
                   const PI_Wheel_Encoder& motion_cmd_in,
                   const PI_Laser_Scan& laser_scan_in,
                   const PI_Vehicle_Parameters& params_in,
                   PI_Wheel_Encoder& motion_cmd_out);

#endif