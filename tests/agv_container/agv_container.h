
/**
* @brief This file contains all laser scan interface types
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __TESTS_AGV_CONTAINER_AGV_CONTAINER_H__
#define __TESTS_AGV_CONTAINER_AGV_CONTAINER_H__

#include <chrono>
#include <string>
#include <vector>
#include "gazebo_interface.h"
#include "pi/headers/aggregate_types_guidance.h"
#include "pi/headers/aggregate_types_laser_scan.h"
#include "pi/headers/aggregate_types_odometry.h"
#include "pi/headers/aggregate_types_sensor_fusion.h"
#include "pi/headers/aggregate_types_supervisor.h"
#include "pi/headers/aggregate_types_vehicle_parameters.h"

class AGVContainer {
 public:
  explicit AGVContainer() {
    // initialize the system
    agv_container_init();
  }

  // Deleted copy constructor
  AGVContainer(const AGVContainer&) = delete;

  // Default move constructor
  AGVContainer(AGVContainer&&) = default;

  // Deleted copy assignment operator
  AGVContainer& operator=(const AGVContainer&) = delete;

  // Default move assignment operator
  AGVContainer& operator=(AGVContainer&&) = delete;

  // destructor
  ~AGVContainer() {}

  void UpdatePIContainers();

  template <class T>
  void WriteData(const T& sensor_in_, Gazebo_Out_Data& gazebo_data_out_);

  template <class T>
  void ReadData(const Gazebo_In_Data& gazebo_data_in_, const T& sensor_out_);

  // initialize the floor plan
  void LoadMoves(PI_Moves& moves);
  void LoadFloorTargets(PI_Floor_Targets& targets);
  void LoadNodes(PI_Floor_Nodes& nodes);

  // 3 next moves from the host
  void SetNextThreeMoves(std::vector<std::string>& moves);

  // set the tables
  void SetMoveTable(std::vector<std::vector<std::string>>& move_table);
  void SetNodeTable(std::vector<std::vector<std::string>>& node_table);
  void SetTargetTable(std::vector<std::vector<std::string>>& target_table);

 private:
  // odometry inputs
  PI_Wheel_Encoder wheel_encoders_odometry_in_;
  PI_Odometry_Pose odometry_pose_in_;
  PI_Wheel_Encoder odometry_motion_cmd_in_;

  // sensor fusion inputs
  PI_Laser_Scan scanner_in_;
  PI_Floor_Targets floor_targets_in_;
  PI_Odometry_Pose fused_pose_out_;

  // motion control inputs
  PI_Wheel_Encoder motion_sensors_in_;
  PI_Vehicle_Parameters vehicle_params_in_;

  // guidance inputs
  PI_Supervisor_Status supervisor_in_;
  PI_Floor_Nodes floor_nodes_in_;
  PI_Moves moves_in_;
  PI_Move_Cmd move_cmd_in_;

  // guidance output
  PI_Wheel_Encoder guidance_cmd_out_;

  // odometry outputs or guidance pose in
  PI_Odometry_Pose odometry_pose_out_;

  // motion control
  PI_Wheel_Encoder motion_cmd_out_;

  // periodic timestamps
  std::chrono::system_clock::time_point last_timestamp;
  uint8_t periodic_looptime_;

  // agv container init
  void agv_container_init(void);
};

#endif