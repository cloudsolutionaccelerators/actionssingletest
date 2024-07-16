/**
* @brief This file contains guidance adapters
*        from translating current signals to the
*        platform independent types.
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __ADAPTERS_GUIDANCE_H__
#define __ADAPTERS_GUIDANCE_H__

#include "pd/headers/pd_data_types.h"
#include "pi/headers/aggregate_types_guidance.h"
#include "pi/headers/aggregate_types_laser_scan.h"
#include "pi/headers/aggregate_types_odometry.h"
#include "pi/headers/aggregate_types_sensor_fusion.h"
#include "pi/headers/aggregate_types_supervisor.h"
#include "pi/headers/aggregate_types_vehicle_parameters.h"

namespace adapters::guidance {
using namespace pd::agv;
void convert(const Odometry_Pose& input, PI_Odometry_Pose& output);
void convert(const Supervisor_Status& input, PI_Supervisor_Status& output);
void convert(const Floor_Targets& input, PI_Floor_Targets& output);
void convert(const Floor_Nodes& input, PI_Floor_Nodes& output);
void convert(const Moves& input, PI_Moves& output);
void convert(const Move_Cmd& input, PI_Move_Cmd& output);
void convert(const Wheel_Encoder& input, PI_Wheel_Encoder& output);
void convert(const Laser_Scan& input, PI_Laser_Scan& output);
void convert(const Vehicle_Parameters& input, PI_Vehicle_Parameters& output);
void convert(const PI_Wheel_Encoder& input, Wheel_Encoder& output);
void invalidate(PI_Odometry_Pose& output);
void invalidate(PI_Supervisor_Status& output);
void invalidate(PI_Wheel_Encoder& output);
void invalidate(PI_Laser_Scan& output);
void invalidate(PI_Move_Cmd& output);
}  // namespace adapters::guidance

#endif