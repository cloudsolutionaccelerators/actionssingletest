/**
* @brief This file contains guidance interface types
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __INTERFACES_PI_HEADERS_AGGREGATE_TYPES_GUIDANCE_H__
#define __INTERFACES_PI_HEADERS_AGGREGATE_TYPES_GUIDANCE_H__

#include <cstdint>
#include <string>
#include <vector>

/// <summary>
/// Shop Floor Node Info
/// </summary>
typedef struct PI_Floor_Node_Info_ {
  using float32_t = float;

  uint16_t node_id;
  float32_t x;
  float32_t y;

  // this is in degrees
  float32_t path_heading;
  float32_t veh_heading;

  uint16_t floor;
  std::string desc;
  uint16_t vtb_index;

  // these definitions will be laid out
  // once they are available
  uint16_t stop_type;
  uint16_t stop_type_usr_gen;
  uint16_t dest_only;
  uint16_t restart_allowed;
  uint16_t auto_restart_allowed;
  uint16_t lane_node;
  uint16_t max_lane;
  float32_t lane_node_speed;
  uint16_t restart_script;
  uint16_t arrive_script;
  uint16_t depart_script;
  uint16_t disp_str_id;
  uint16_t use_soft_approach;

} PI_Floor_Node_Info;

#define PI_MAX_TARGET_NODES (65535)

/// <summary>
/// Shop Floor Node Info
/// </summary>
typedef struct PI_Floor_Nodes_ {
  uint16_t num_nodes;
  PI_Floor_Node_Info node[PI_MAX_TARGET_NODES];
} PI_Floor_Nodes;

/// <summary>
/// Trajectory types
/// </summary>
enum PI_Trajectory_type {
  CLOTHOID,
  PIVOT,
  CRABBING_CLOTHOID,
  ANTIPARALLEL_CLOTHOID,
  DUMMY
};

/// <summary>
/// Move Info
/// </summary>
typedef struct PI_Move_Info_ {
  using float32_t = float;

  std::string move_id;
  uint16_t start_node;
  uint16_t end_node;

  // speed in meters/sec
  float32_t max_speed;

  PI_Trajectory_type trajectory;
  uint16_t vtb_index;
  uint16_t host_aplus_header;
  uint16_t host_aplus_trailer;
  uint16_t veh_aplus_header;
  uint16_t veh_aplus_trailer;

  // constrained speed in meters/sec
  float32_t constrained_speed;

  // angle in degrees
  float32_t max_steer_angle;

} PI_Move_Info;

#define PI_MAX_MOVES (65535)

/// <summary>
/// Moves
/// </summary>
typedef struct PI_Moves_ {
  uint16_t num_moves;
  PI_Move_Info node[PI_MAX_MOVES];
} PI_Moves;

/// <summary>
/// Move Cmd from the Host
/// </summary>
typedef struct PI_Move_Cmd_ {
  uint16_t num_moves;
  std::vector<std::string> moves;
} PI_Move_Cmd;

#endif