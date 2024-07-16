/**
* @brief This file implements adapters for guidance
*        converting to and from host interfaces to
*        to the platform independent types
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/
#include "adapters/include/guidance.h"

namespace adapters::guidance {
using namespace pd::agv;
void convert([[maybe_unused]] const Odometry_Pose& input,
             [[maybe_unused]] PI_Odometry_Pose& output) {}
void convert([[maybe_unused]] const Supervisor_Status& input,
             [[maybe_unused]] PI_Supervisor_Status& output) {}
void convert([[maybe_unused]] const Floor_Targets& input,
             [[maybe_unused]] PI_Floor_Targets& output) {}
void convert([[maybe_unused]] const Floor_Nodes& input,
             [[maybe_unused]] PI_Floor_Nodes& output) {}
void convert([[maybe_unused]] const Moves& input,
             [[maybe_unused]] PI_Moves const& output) {}
void convert([[maybe_unused]] const Move_Cmd& input,
             [[maybe_unused]] PI_Move_Cmd& output) {}
void convert([[maybe_unused]] const Wheel_Encoder& input,
             [[maybe_unused]] PI_Wheel_Encoder& output) {}
void convert([[maybe_unused]] const Laser_Scan& input,
             [[maybe_unused]] PI_Laser_Scan& output) {}
void convert([[maybe_unused]] const Vehicle_Parameters& input,
             [[maybe_unused]] PI_Vehicle_Parameters& output) {}
void convert([[maybe_unused]] const PI_Wheel_Encoder& input,
             [[maybe_unused]] Wheel_Encoder& output) {}

// Some error handling and data defaulting
void invalidate([[maybe_unused]] PI_Odometry_Pose& output) {}
void invalidate([[maybe_unused]] PI_Supervisor_Status& output) {}
void invalidate([[maybe_unused]] PI_Move_Cmd& output) {}
void invalidate([[maybe_unused]] PI_Wheel_Encoder& output) {}
void invalidate([[maybe_unused]] PI_Laser_Scan& output) {}
}  // namespace adapters::guidance