/**
* @brief This file contains AGV Container PI module
*        updates.
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#include "agv_container.h"
#include <chrono>
#include <string>
#include <thread>
#include <vector>
#include "pi/headers/container_guidance.h"
#include "pi/headers/container_motion_control.h"
#include "pi/headers/container_odometry.h"
#include "pi/headers/container_sensor_fusion.h"

/// @brief This is the pi container periodic
///        update cycle.
void AGVContainer::UpdatePIContainers() {

  // update the odometry
  PI_Odometry_S(wheel_encoders_odometry_in_, odometry_pose_in_,
                odometry_motion_cmd_in_, vehicle_params_in_,
                odometry_pose_out_);

  // update sensor fusion
  PI_Sensor_Fusion_S(odometry_pose_out_, scanner_in_, floor_targets_in_,
                     fused_pose_out_);

  // update the guidance
  PI_Guidance_S(fused_pose_out_, supervisor_in_, floor_targets_in_,
                floor_nodes_in_, moves_in_, move_cmd_in_, motion_cmd_out_,
                scanner_in_, vehicle_params_in_, guidance_cmd_out_);

  // update the motion control
  PI_Motion_Control_S(guidance_cmd_out_, motion_sensors_in_, vehicle_params_in_,
                      motion_cmd_out_);

  // now repeat the cycle every 30ms
  auto now = std::chrono::system_clock::now();
  auto duration = now - last_timestamp;
  auto millis =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  if (millis < periodic_looptime_) {
    // Wait for the remaining time
    std::this_thread::sleep_for(
        std::chrono::milliseconds(periodic_looptime_ - millis));
  } else {
    // Perform read operation here
    last_timestamp = now;
  }
}

/// @brief This is the steering angle sensor data.
template <class T>
void AGVContainer::WriteData(const T& sensor_in_,
                             Gazebo_Out_Data& gazebo_data_out_) {
  // 4 steering sensors, all identical
  gazebo_data_out_.steering_angle.push_back(sensor_in_);
  gazebo_data_out_.steering_angle.push_back(sensor_in_);
  gazebo_data_out_.steering_angle.push_back(sensor_in_);
  gazebo_data_out_.steering_angle.push_back(sensor_in_);
}

/// @brief This is the system initialize.
void AGVContainer::agv_container_init(void) {
  // evaluate the outputs
  for (uint8_t i = 0; i < PI_NUMBER_OF_WHEEL_ENCODERS; i++) {
    motion_cmd_out_.data[i].rotation_speed = 0.0F;
    motion_cmd_out_.data[i].steering_angle = 0.0F;
  }

  // setup the wheelbase and wheel diameter
  vehicle_params_in_.wheel.wheel_diameter = 0.15;
  vehicle_params_in_.wheel.wheelbase = 0.5;

  // initialize looptime
  periodic_looptime_ = 30U;
}

/// @brief This sets the moves from the host
void AGVContainer::SetNextThreeMoves(std::vector<std::string>& moves) {
  move_cmd_in_.num_moves = moves.size();

  for (uint8_t i = 0; i < move_cmd_in_.num_moves; i++)
    move_cmd_in_.moves[i] = moves[i];
}

/// @brief This sets the moves table
void AGVContainer::SetMoveTable(
    std::vector<std::vector<std::string>>& move_table) {
  moves_in_.num_moves = move_table.size();
  for (uint8_t i = 0; i < move_table.size(); i++) {
    moves_in_.node[i].move_id = move_table[i][0];
    moves_in_.node[i].start_node = std::stoi(move_table[i][1]);
    moves_in_.node[i].end_node = std::stoi(move_table[i][2]);
    moves_in_.node[i].max_speed = std::stof(move_table[i][3]);
    moves_in_.node[i].trajectory =
        static_cast<PI_Trajectory_type>(std::stoi(move_table[i][4]));
  }
}

/// @brief This sets the node table
void AGVContainer::SetNodeTable(
    std::vector<std::vector<std::string>>& node_table) {
  floor_nodes_in_.num_nodes = node_table.size();
  for (uint8_t i = 0; i < node_table.size(); i++) {
    floor_nodes_in_.node[i].node_id = std::stoi(node_table[i][0]);
    floor_nodes_in_.node[i].x = std::stof(node_table[i][1]);
    floor_nodes_in_.node[i].y = std::stof(node_table[i][2]);
    floor_nodes_in_.node[i].path_heading = std::stof(node_table[i][3]);
    floor_nodes_in_.node[i].veh_heading = std::stof(node_table[i][4]);
    floor_nodes_in_.node[i].floor = std::stoi(node_table[i][5]);
  }
}
/// @brief This sets the target table
void AGVContainer::SetTargetTable(
    std::vector<std::vector<std::string>>& target_table) {
  floor_nodes_in_.num_nodes = target_table.size();
  for (uint8_t i = 0; i < target_table.size(); i++) {
    floor_targets_in_.node[i].node_id = std::stoi(target_table[i][0]);
    floor_targets_in_.node[i].x = std::stof(target_table[i][1]);
    floor_targets_in_.node[i].y = std::stof(target_table[i][2]);
    floor_targets_in_.node[i].heading = std::stof(target_table[i][3]);
    floor_targets_in_.node[i].type = std::stoi(target_table[i][4]);
    floor_targets_in_.node[i].floor = std::stoi(target_table[i][5]);
  }
}
