/**
* @brief This file contains the pi container interface for 
*        sensor fusion component
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __INTERFACES_PI_HEADERS_CONTAINER_SENSOR_FUSION_H__
#define __INTERFACES_PI_HEADERS_CONTAINER_SENSOR_FUSION_H__

#include "pi/headers/aggregate_types_laser_scan.h"
#include "pi/headers/aggregate_types_odometry.h"

/// <summary>
/// Container interface for sensor fusion component Init
/// </summary>

void PI_Sensor_Fusion_I(const PI_Odometry_Pose& pose_in,
                        const PI_Laser_Scan& scanner_in,
                        const PI_Floor_Targets& floor_targets_in,
                        PI_Odometry_Pose& fused_pose_out);

/// <summary>
/// Container interface for sensor fusion component step function
/// </summary>
void PI_Sensor_Fusion_S(const PI_Odometry_Pose& pose_in,
                        const PI_Laser_Scan& scanner_in,
                        const PI_Floor_Targets& floor_targets_in,
                        PI_Odometry_Pose& fused_pose_out);

#endif