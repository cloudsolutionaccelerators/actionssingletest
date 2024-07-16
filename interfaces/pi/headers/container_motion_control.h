/**
* @brief This file contains the pi container interface for 
*        motion control component
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __INTERFACES_PI_HEADERS_CONTAINER_MOTION_CONTROL_H__
#define __INTERFACES_PI_HEADERS_CONTAINER_MOTION_CONTROL_H__

#include "pi/headers/aggregate_types_odometry.h"
#include "pi/headers/aggregate_types_vehicle_parameters.h"

/// <summary>
/// Container interface for motion control component Init
/// </summary>

void PI_Motion_Control_I(const PI_Wheel_Encoder& motion_desired_in,
                         const PI_Wheel_Encoder& sensors_in,
                         const PI_Vehicle_Parameters& parameters_in,
                         PI_Wheel_Encoder& motion_cmd_out);

/// <summary>
/// Container interface for motion control component Step
/// </summary>
void PI_Motion_Control_S(const PI_Wheel_Encoder& motion_desired_in,
                         const PI_Wheel_Encoder& sensors_in,
                         const PI_Vehicle_Parameters& parameters_in,
                         PI_Wheel_Encoder& motion_cmd_out);

#endif