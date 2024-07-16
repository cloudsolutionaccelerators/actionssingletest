/**
* @brief This file contains all sensor fusion interface types
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __INTERFACES_PI_HEADERS_AGGREGATE_TYPES_SENSOR_FUSION_H__
#define __INTERFACES_PI_HEADERS_AGGREGATE_TYPES_SENSOR_FUSION_H__

#include <cstdint>

/// <summary>
/// Shop Floor Target Layout
/// </summary>
typedef struct PI_Floor_Target_Layout_ {
  using float32_t = float;

  uint16_t node_id;
  float32_t x;
  float32_t y;

  // this is in degrees
  float32_t heading;

  uint16_t type;
  uint16_t floor;

} PI_Floor_Target_Layout;

#define PI_MAX_TARGET_NODES (65535)

/// <summary>
/// Shop Floor TargetS
/// </summary>
typedef struct PI_Floor_Targets_ {
  uint16_t num_nodes;
  PI_Floor_Target_Layout node[PI_MAX_TARGET_NODES];
} PI_Floor_Targets;

#endif