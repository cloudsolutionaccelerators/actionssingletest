/**
* @brief This file contains all supervisor types
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __INTERFACES_PI_HEADERS_AGGREGATE_TYPES_SUPERVISOR_H__
#define __INTERFACES_PI_HEADERS_AGGREGATE_TYPES_SUPERVISOR_H__

#include <string>

/// <summary>
/// This contains the  status of faults and diagnostics
/// </summary>
typedef struct PI_FADC_Status_ {
  /// @brief  low severity
  bool level1;

  /// @brief  med severity
  bool level2;

  /// @brief  high severity
  bool level3;
} PI_FADC_Status;

#define PI_MAX_FWD_CMDS (3)

/// <summary>
/// This contains the  node structure
/// </summary>
typedef struct PI_Command_Info_ {
  // Number of commands in pipeline
  uint8_t num_cmds;

  /// This is the command structure from host
  std::string commands[PI_MAX_FWD_CMDS];

} PI_Command_Info;

/// <summary>
/// This contains the  status of the supervisor
/// </summary>
typedef struct PI_Supervisor_Status_ {
  /// Command Info
  PI_Command_Info cmds;

  /// This flag indicates faults
  PI_FADC_Status faults;

  /// battery level
  double battery_level;

  /// estop command
  bool estop_pressed;

} PI_Supervisor_Status;

#endif