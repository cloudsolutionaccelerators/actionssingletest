/**
* @brief This file contains the pi container interface for 
*        odometry component
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __INTERFACES_PI_HEADERS_CONTAINER_ODOMETRY_H__
#define __INTERFACES_PI_HEADERS_CONTAINER_ODOMETRY_H__

#include "pi/headers/aggregate_types_odometry.h"
#include "pi/headers/aggregate_types_vehicle_parameters.h"

/// <summary>
/// Container interface for odometry component Init
/// </summary>

void PI_Odometry_I(const PI_Wheel_Encoder& wheel_encoders_in,
                   const PI_Odometry_Pose& pose_in,
                   const PI_Wheel_Encoder& motion_cmd_in,
                   const PI_Vehicle_Parameters& parameters_in,
                   PI_Odometry_Pose& odometry_pose_out);

/// <summary>
/// Container interface for odometry component step function
/// </summary>
void PI_Odometry_S(const PI_Wheel_Encoder& wheel_encoders_in,
                   const PI_Odometry_Pose& pose_in,
                   const PI_Wheel_Encoder& motion_cmd_in,
                   const PI_Vehicle_Parameters& parameters_in,
                   PI_Odometry_Pose& odometry_pose_out);

#endif