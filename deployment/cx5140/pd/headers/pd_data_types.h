/**
* @brief This file contains interface types
*        that are current platform dependent. This
*        defines the current A+ types
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __PD_HEADERS_PD_DATA_TYPES_H__
#define __PD_HEADERS_PD_DATA_TYPES_H__

#include <cstdint>

namespace pd::agv {
/// <summary>
/// Moves
/// </summary>
typedef struct Moves_ {
  Moves_() {}
} Moves;

/// <summary>
/// Pose
/// </summary>
typedef struct Odometry_Pose_ {
  Odometry_Pose_() {}
} Odometry_Pose;

/// <summary>
/// Supervisor Status
/// </summary>
typedef struct Supervisor_Status_ {
  Supervisor_Status_() {}
} Supervisor_Status;

/// <summary>
/// Floor Nodes
/// </summary>
typedef struct Floor_Nodes_ {
  Floor_Nodes_() {}
} Floor_Nodes;

/// <summary>
/// Move Cmds
/// </summary>
typedef struct Move_Cmd_ {
  Move_Cmd_() {}
} Move_Cmd;

/// <summary>
/// Wheel encoders
/// </summary>
typedef struct Wheel_Encoder_ {
  Wheel_Encoder_() {}
} Wheel_Encoder;

/// <summary>
/// Laser scan
/// </summary>
typedef struct Laser_Scan_ {
  Laser_Scan_() {}
} Laser_Scan;

/// <summary>
/// Floor_Targets
/// </summary>
typedef struct Floor_Targets_ {
  Floor_Targets_() {}
} Floor_Targets;

/// <summary>
/// Vehicle Parameters
/// </summary>
typedef struct Vehicle_Parameters_ {
  Vehicle_Parameters_() {}
} Vehicle_Parameters;
}  // namespace pd::agv

/// <summary>
/// Init and Step for guidance
/// </summary>
void Guidance_I(void);
void Guidance_S(void);

#endif