/**
* @brief This file contains main Sensor_Fusion class
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __MODULES_PI_SENSOR_FUSION_INCLUDE_SENSOR_FUSION_H__
#define __MODULES_PI_SENSOR_FUSION_INCLUDE_SENSOR_FUSION_H__

#include <Eigen/Dense>
#include "pi/headers/aggregate_types_guidance.h"
#include "pi/headers/aggregate_types_laser_scan.h"
#include "pi/headers/aggregate_types_odometry.h"
#include "pi/headers/aggregate_types_sensor_fusion.h"

/// <summary>
/// The main Sensor Fusion class
/// </summary>
namespace agv::sensor_fusion {
class Sensor_Fusion {
 public:
  explicit Sensor_Fusion(const PI_Odometry_Pose& pose_in,
                         const PI_Laser_Scan& scanner_in,
                         const PI_Floor_Targets& floor_targets_in,
                         PI_Odometry_Pose& fused_pose_out)
      : pose_in_(pose_in),
        scanner_in_(scanner_in),
        floor_targets_in_(floor_targets_in),
        fused_pose_out_(fused_pose_out) {
    state_ = Eigen::Vector3f::Zero();
    P_ = Eigen::Matrix3f::Identity();
    measurement_ = Eigen::Vector3f::Random();
  }

  // Deleted copy constructor
  Sensor_Fusion(const Sensor_Fusion&) = delete;

  // Default move constructor
  Sensor_Fusion(Sensor_Fusion&&) = default;

  // Deleted copy assignment operator
  Sensor_Fusion& operator=(const Sensor_Fusion&) = delete;

  // Default move assignment operator
  Sensor_Fusion& operator=(Sensor_Fusion&&) = delete;

  // destructor
  ~Sensor_Fusion() {}

  void run();

 private:
  const PI_Odometry_Pose& pose_in_;
  const PI_Laser_Scan& scanner_in_;
  const PI_Floor_Targets& floor_targets_in_;
  PI_Odometry_Pose& fused_pose_out_;

  Eigen::Matrix3f B_;
  Eigen::Matrix3f C_;
  Eigen::Matrix3f Q_;
  Eigen::Matrix3f R_;
  Eigen::Matrix3f P_;
  Eigen::Matrix3f I_;
  Eigen::Matrix3f K_;
  Eigen::Vector3f state_;
  Eigen::Vector3f measurement_;
  void state_machine(void);

  /// <summary>
  /// prediction just uses the odometry
  /// </summary>
  void predict() {
    Eigen::Matrix<float, 3, 1> odom;
    odom << pose_in_.x, pose_in_.y, pose_in_.heading;
    state_ = state_ + odom;
    P_ = P_ + Q_;
  }

  /// <summary>
  /// This uses the laser measurement. TBD
  /// </summary>
  void update() {
    Eigen::Vector3f innovation = measurement_ - C_ * state_;
    Eigen::Matrix3f innovation_covariance = C_ * P_ * C_.transpose() + R_;
    K_ = P_ * C_.transpose() * innovation_covariance.inverse();
    state_ = state_ + K_ * innovation;
    P_ = (I_ - K_ * C_) * P_;

    // update the output
    fused_pose_out_.x = state_(0);
    fused_pose_out_.y = state_(1);
    fused_pose_out_.heading = state_(2);
  }
};
}  // namespace agv::sensor_fusion

#endif