/**
* @brief This file contains the test fixture for Guidance
*        pd container
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __PD_CONTAINERS_GUIDANCE_TESTS_GUIDANCE_H__
#define __PD_CONTAINERS_GUIDANCE_TESTS_GUIDANCE_H__

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <cmath>
#include <functional>
#include <iostream>
#include "pd/headers/pd_data_handlers.h"
#include "pd/headers/pd_data_types.h"
#include "pd/headers/pd_wrappers.h"
#include "pi/headers/aggregate_types_guidance.h"
#include "pi/headers/aggregate_types_laser_scan.h"
#include "pi/headers/aggregate_types_odometry.h"
#include "pi/headers/aggregate_types_sensor_fusion.h"
#include "pi/headers/aggregate_types_vehicle_parameters.h"
#include "pi/headers/container_guidance.h"

namespace pd::guidance {

using ::testing::_;
using ::testing::DoAll;
using ::testing::HasSubstr;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::SetArgReferee;
using ::testing::internal::CaptureStderr;
using ::testing::internal::GetCapturedStderr;

class PIBaseGuidance {
 public:
  PIBaseGuidance() {}
  virtual ~PIBaseGuidance() {}
  virtual void PI_Guidance_I(const PI_Odometry_Pose&,
                             const PI_Supervisor_Status&,
                             const PI_Floor_Targets&, const PI_Floor_Nodes&,
                             const PI_Moves&, const PI_Move_Cmd&,
                             const PI_Wheel_Encoder&, const PI_Laser_Scan&,
                             const PI_Vehicle_Parameters&,
                             PI_Wheel_Encoder&) = 0;
  virtual void PI_Guidance_S(const PI_Odometry_Pose&,
                             const PI_Supervisor_Status&,
                             const PI_Floor_Targets&, const PI_Floor_Nodes&,
                             const PI_Moves&, const PI_Move_Cmd&,
                             const PI_Wheel_Encoder&, const PI_Laser_Scan&,
                             const PI_Vehicle_Parameters&,
                             PI_Wheel_Encoder&) = 0;
};

class MockPIContainer : public PIBaseGuidance {
 public:
  MOCK_METHOD(void, PI_Guidance_I,
              (const PI_Odometry_Pose&, const PI_Supervisor_Status&,
               const PI_Floor_Targets&, const PI_Floor_Nodes&, const PI_Moves&,
               const PI_Move_Cmd&, const PI_Wheel_Encoder&,
               const PI_Laser_Scan&, const PI_Vehicle_Parameters&,
               PI_Wheel_Encoder&),
              (override));
  MOCK_METHOD(void, PI_Guidance_S,
              (const PI_Odometry_Pose&, const PI_Supervisor_Status&,
               const PI_Floor_Targets&, const PI_Floor_Nodes&, const PI_Moves&,
               const PI_Move_Cmd&, const PI_Wheel_Encoder&,
               const PI_Laser_Scan&, const PI_Vehicle_Parameters&,
               PI_Wheel_Encoder&),
              (override));
};

class MockIOData {
 public:
  MockIOData();
  virtual ~MockIOData();
  MOCK_METHOD1(Read_Move_Cmd_From_Host,
               pd::wrappers::Std_ReturnType(pd::agv::Move_Cmd&));
  MOCK_METHOD1(Read_Moves_From_Config,
               pd::wrappers::Std_ReturnType(pd::agv::Moves&));
  MOCK_METHOD1(Read_Floor_Targets_From_Config,
               pd::wrappers::Std_ReturnType(pd::agv::Floor_Targets&));
  MOCK_METHOD1(Read_Pose_From_Sensor_Fusion,
               pd::wrappers::Std_ReturnType(pd::agv::Odometry_Pose&));
  MOCK_METHOD1(Read_Status_From_Supervisor,
               pd::wrappers::Std_ReturnType(pd::agv::Supervisor_Status&));
  MOCK_METHOD1(Read_Nodes_From_Config,
               pd::wrappers::Std_ReturnType(pd::agv::Floor_Nodes&));
  MOCK_METHOD1(Read_Motion_Cmd_From_Motion_Control,
               pd::wrappers::Std_ReturnType(pd::agv::Wheel_Encoder&));
  MOCK_METHOD1(Read_Laser_Scan_From_IO,
               pd::wrappers::Std_ReturnType(pd::agv::Laser_Scan&));
  MOCK_METHOD1(Read_Vehicle_Parameters_From_Config,
               pd::wrappers::Std_ReturnType(pd::agv::Vehicle_Parameters&));
  MOCK_METHOD1(Write_Cmd_To_Motion_Control,
               pd::wrappers::Std_ReturnType(pd::agv::Wheel_Encoder&));
};

static MockIOData* mock_ptr = nullptr;

void setMock(MockIOData* mock) {
  mock_ptr = mock;
}
void clearMock() {
  mock_ptr = nullptr;
}
MockIOData::MockIOData() {
  setMock(this);
}
MockIOData::~MockIOData() {
  clearMock();
}
void setUpMocks(MockIOData& mock) {
  ON_CALL(mock, Read_Move_Cmd_From_Host(_))
      .WillByDefault(Return(pd::wrappers::Std_ReturnType::READ_OK));
  ON_CALL(mock, Read_Moves_From_Config(_))
      .WillByDefault(Return(pd::wrappers::Std_ReturnType::READ_OK));
  ON_CALL(mock, Read_Floor_Targets_From_Config(_))
      .WillByDefault(Return(pd::wrappers::Std_ReturnType::READ_OK));
  ON_CALL(mock, Read_Pose_From_Sensor_Fusion(_))
      .WillByDefault(Return(pd::wrappers::Std_ReturnType::READ_OK));
  ON_CALL(mock, Read_Status_From_Supervisor(_))
      .WillByDefault(Return(pd::wrappers::Std_ReturnType::READ_OK));
  ON_CALL(mock, Read_Nodes_From_Config(_))
      .WillByDefault(Return(pd::wrappers::Std_ReturnType::READ_OK));
  ON_CALL(mock, Read_Motion_Cmd_From_Motion_Control(_))
      .WillByDefault(Return(pd::wrappers::Std_ReturnType::READ_OK));
  ON_CALL(mock, Read_Laser_Scan_From_IO(_))
      .WillByDefault(Return(pd::wrappers::Std_ReturnType::READ_OK));
  ON_CALL(mock, Read_Vehicle_Parameters_From_Config(_))
      .WillByDefault(Return(pd::wrappers::Std_ReturnType::READ_OK));
  ON_CALL(mock, Write_Cmd_To_Motion_Control(_))
      .WillByDefault(Return(pd::wrappers::Std_ReturnType::READ_OK));
}
class TestGuidance : public ::testing::Test {
 public:
  TestGuidance() {}
  virtual ~TestGuidance() {}
  void SetUp() {
    onPICalls();
    expectPICalls();
    setUpMocks(mock_io_);
    Guidance_I();
  }
  void TearDown() {}
  void onPICalls() {
    ON_CALL(mock_pi_, PI_Guidance_I(_, _, _, _, _, _, _, _, _, _))
        .WillByDefault([]() { return; });
    ON_CALL(mock_pi_, PI_Guidance_S(_, _, _, _, _, _, _, _, _, _))
        .WillByDefault([]() { return; });
  }
  void expectPICalls() {
    EXPECT_CALL(mock_pi_, PI_Guidance_I(_, _, _, _, _, _, _, _, _, _)).Times(1);
    EXPECT_CALL(mock_pi_, PI_Guidance_S(_, _, _, _, _, _, _, _, _, _)).Times(1);
  }

  void run(void) { Guidance_S(); }

  void run_for(float seconds, const std::function<void()>& callback =
                                  std::function<void()>()) {
    std::size_t const kNumOfSamples = static_cast<std::size_t>(seconds * 34U);
    std::size_t counter = 0U;

    while (counter < kNumOfSamples) {
      run();
      ++counter;

      if (callback)
        callback();
    }
  }

  void runWithWriteError() {
    CaptureStderr();
    Guidance_S();
    const std::string output = GetCapturedStderr();
    EXPECT_THAT(output, HasSubstr("write failed"));
  }

  void runWithReadError() {
    CaptureStderr();
    Guidance_S();
    const std::string output = GetCapturedStderr();
    EXPECT_THAT(output, HasSubstr("read failed"));
  }

 protected:
  PI_Odometry_Pose fused_pose_in_;
  PI_Supervisor_Status supervisor_in_;
  PI_Floor_Targets floor_targets_in_;
  PI_Floor_Nodes floor_nodes_in_;
  PI_Moves moves_in_;
  PI_Move_Cmd move_cmd_in_;
  PI_Wheel_Encoder motion_cmd_in_;
  PI_Laser_Scan laser_scan_in_;
  PI_Vehicle_Parameters params_in_;
  PI_Wheel_Encoder guidance_cmd_out_;

  MockPIContainer mock_pi_;
  NiceMock<MockIOData> mock_io_;
};

void expectCalls(MockIOData& mock) {
  EXPECT_CALL(mock, Read_Move_Cmd_From_Host(_)).Times(1);
  EXPECT_CALL(mock, Read_Moves_From_Config(_)).Times(1);
  EXPECT_CALL(mock, Read_Floor_Targets_From_Config(_)).Times(1);
  EXPECT_CALL(mock, Read_Pose_From_Sensor_Fusion(_)).Times(1);
  EXPECT_CALL(mock, Read_Status_From_Supervisor(_)).Times(1);
  EXPECT_CALL(mock, Read_Nodes_From_Config(_)).Times(1);
  EXPECT_CALL(mock, Read_Motion_Cmd_From_Motion_Control(_)).Times(1);
  EXPECT_CALL(mock, Read_Laser_Scan_From_IO(_)).Times(1);
  EXPECT_CALL(mock, Read_Vehicle_Parameters_From_Config(_)).Times(1);
  EXPECT_CALL(mock, Write_Cmd_To_Motion_Control(_)).Times(1);
}
pd::wrappers::Std_ReturnType Read_Move_Cmd_From_Host(pd::agv::Move_Cmd& data) {
  return mock_ptr->Read_Move_Cmd_From_Host(data);
}
pd::wrappers::Std_ReturnType Read_Floor_Targets_From_Config(
    pd::agv::Floor_Targets& data) {
  return mock_ptr->Read_Floor_Targets_From_Config(data);
}
pd::wrappers::Std_ReturnType Read_Moves_From_Config(pd::agv::Moves& data) {
  return mock_ptr->Read_Moves_From_Config(data);
}
pd::wrappers::Std_ReturnType Read_Pose_From_Sensor_Fusion(
    pd::agv::Odometry_Pose& data) {
  return mock_ptr->Read_Pose_From_Sensor_Fusion(data);
}
pd::wrappers::Std_ReturnType Read_Status_From_Supervisor(
    pd::agv::Supervisor_Status& data) {
  return mock_ptr->Read_Status_From_Supervisor(data);
}
pd::wrappers::Std_ReturnType Read_Nodes_From_Config(
    pd::agv::Floor_Nodes& data) {
  return mock_ptr->Read_Nodes_From_Config(data);
}
pd::wrappers::Std_ReturnType Read_Motion_Cmd_From_Motion_Control(
    pd::agv::Wheel_Encoder& data) {
  return mock_ptr->Read_Motion_Cmd_From_Motion_Control(data);
}
pd::wrappers::Std_ReturnType Read_Laser_Scan_From_IO(
    pd::agv::Laser_Scan& data) {
  return mock_ptr->Read_Laser_Scan_From_IO(data);
}
pd::wrappers::Std_ReturnType Read_Vehicle_Parameters_From_Config(
    pd::agv::Vehicle_Parameters& data) {
  return mock_ptr->Read_Vehicle_Parameters_From_Config(data);
}
pd::wrappers::Std_ReturnType Write_Cmd_To_Motion_Control(
    pd::agv::Wheel_Encoder& data) {
  return mock_ptr->Write_Cmd_To_Motion_Control(data);
}
}  // namespace pd::guidance
#endif