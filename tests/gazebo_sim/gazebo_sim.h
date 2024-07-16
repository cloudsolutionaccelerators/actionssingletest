/**
* @brief This file contains gazebo sim app class
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __TESTS_GAZEBO_SIM_GAZEBO_SIM_H__
#define __TESTS_GAZEBO_SIM_GAZEBO_SIM_H__

#include <gz/plugin/Register.hh>
#include <gz/sim/EntityComponentManager.hh>
#include <gz/sim/System.hh>
#include <gz/sim/components/Link.hh>
#include <gz/sim/components/Name.hh>
#include <gz/sim/components/ParentEntity.hh>
#include <gz/sim/components/Pose.hh>

#include <iostream>
#include <string>
#include <vector>
#include "agv_container.h"
#include "gazebo_interface.h"

using namespace gz;
using namespace sim;
using namespace systems;

class GazeboSimulation : public System,
                         public ISystemConfigure,
                         public ISystemPostUpdate {
  virtual void Configure(const Entity& _entity,
                         const std::shared_ptr<const sdf::Element>& _sdf,
                         EntityComponentManager& _ecm,
                         [[maybe_unused]] EventManager& _eventMgr) override {
    // Read property from SDF
    auto linkName = _sdf->Get<std::string>("link_name");

    // Get link entity by querying for an entity that has a specific set of
    // components
    this->linkEntity =
        _ecm.EntityByComponents(components::ParentEntity(_entity),
                                components::Name(linkName), components::Link());

    // world model
    gazebo::Entity world_entity = _ecm->GetEntity("world");
    gazebo::WorldComponent* world_component =
        _ecm->GetComponent<gazebo::WorldComponent>(world_entity);
    gazebo::WorldModelPtr world_model = world_component->GetWorldModel();

    // Now you can access the world model data, such as models, lights, etc.
    std::cout << "World model name: " << world_model->GetName() << std::endl;
  }

  virtual void PostUpdate([[maybe_unused]] const UpdateInfo& _info,
                          const EntityComponentManager& _ecm) override {
    // Get link's local pose
    auto pose = _ecm.Component<components::Pose>(this->linkEntity)->Data();

    // Get link's parent entity
    auto parent = _ecm.Component<components::ParentEntity>(this->linkEntity);

    gazebo::Entity entity_id = _ecm->GetEntity("steering_angle");
    gazebo::SensorComponent* sensor_component =
        _ecm->GetComponent<gazebo::SensorComponent>(entity_id);
    gazebo::SensorDataPtr sensor_data = sensor_component->GetSensorData();
    double value = sensor_data->GetDouble(0);

    // Feed data into C++ components
    agv.WriteData(sensor_data, gazebo_data_out_);

    // Update pi components
    agv.UpdatePIContainers();

    // Iterate over parents until world is reached
    while (parent) {
      // Get parent entity's pose
      auto parentPose = _ecm.Component<components::Pose>(parent->Data());
      if (!parentPose)
        break;

      // Add pose
      pose = parentPose->Data() * pose;

      // keep going up the tree
      parent = _ecm.Component<components::ParentEntity>(parent->Data());
    }
  }

  // 3 next moves from the host
  void GetNextThreeMoves(std::vector<std::string>& moves) {
    agv.SetNextThreeMoves(moves);
  }

  void SetMoveTable(std::vector<std::vector<std::string>>& move_table) {
    agv.SetMoveTable(move_table);
  }

  // ID of link entity
 private:
  Entity linkEntity;

  // gazebo data workspace
  Gazebo_In_Data gazebo_in_data_;
  Gazebo_Out_Data gazebo_out_data_;

  // component containers
  AGVContainer agv;
};

// Register the plugin
GZ_ADD_PLUGIN(GazeboSimulation, gz::sim::System,
              GazeboSimulation::ISystemConfigure,
              GazeboSimulation::ISystemPostUpdate)

GZ_ADD_PLUGIN_ALIAS(GazeboSimulation, "gz::sim::systems::GazeboSimulation")

#endif