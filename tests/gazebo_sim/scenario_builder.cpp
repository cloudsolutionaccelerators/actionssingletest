#include <agv_container.h>
#include <gazebo_sim.h>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& line, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream stream(line);
  while (getline(stream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

int main(int argc, char* argv[]) {

  if (argc != 5)
    throw std::runtime_error("syntax: world_model, moves, nodes, targets json");

  // first file is world model
  std::string world_model = argv[0];
  GazeboSimulation gaz_sim(world_model);

  // move files
  std::string moves = argv[1];

  // process the moves file
  std::ifstream file(moves);

  if (!file.is_open()) {
    std::cerr << "Error opening file: " << moves << std::endl;
    return 1;
  }

  std::string line;
  int column_count = 0;

  getline(file, line);
  if (!line.empty()) {
    column_count = split(line, ',').size();
  }

  std::vector<std::vector<std::string>> res;
  while (getline(file, line)) {
    std::vector<std::string> columns = split(line, ',');

    if (static_cast<int>(columns.size()) != column_count && column_count > 0) {
      std::cerr << "Warning: Inconsistent number of columns in line: " << line
                << std::endl;
    }

    for (int i = 0; i < static_cast<int>(columns.size()); ++i) {
      std::cout << "Column " << i + 1 << ": " << columns[i] << std::endl;
    }
    res.push_back(columns);
  }

  gaz_sim.SetMoveTable(res);
  res.clear();

  file.close();

  // nodes and target files
  std::string nodes = argv[2];
  std::string target = argv[3];

  boost::property_tree::ptree pt;
  std::string json_file = argv[4];
  read_json(json_file, pt);

  // process the moves file
  file(nodes);

  if (!file.is_open()) {
    std::cerr << "Error opening file: " << nodes << std::endl;
    return 1;
  }

  line = "";
  column_count = 0;

  getline(file, line);
  if (!line.empty()) {
    column_count = split(line, ',').size();
  }

  res.clear();
  while (getline(file, line)) {
    std::vector<std::string> columns = split(line, ',');

    if (static_cast<int>(columns.size()) != column_count && column_count > 0) {
      std::cerr << "Warning: Inconsistent number of columns in line: " << line
                << std::endl;
    }

    for (int i = 0; i < static_cast<int>(columns.size()); ++i) {
      std::cout << "Column " << i + 1 << ": " << columns[i] << std::endl;
    }
    res.push_back(columns);
  }

  gaz_sim.SetNodeTable(res);
  res.clear();
  file.close();

  // process the moves file
  file(target);

  if (!file.is_open()) {
    std::cerr << "Error opening file: " << nodes << std::endl;
    return 1;
  }

  line = "";
  column_count = 0;

  getline(file, line);
  if (!line.empty()) {
    column_count = split(line, ',').size();
  }

  res.clear();
  while (getline(file, line)) {
    std::vector<std::string> columns = split(line, ',');

    if (static_cast<int>(columns.size()) != column_count && column_count > 0) {
      std::cerr << "Warning: Inconsistent number of columns in line: " << line
                << std::endl;
    }

    for (int i = 0; i < static_cast<int>(columns.size()); ++i) {
      std::cout << "Column " << i + 1 << ": " << columns[i] << std::endl;
    }
    res.push_back(columns);
  }

  gaz_sim.SetTargetTable(res);
  res.clear();
  file.close();

  double secs = pt.get<int>("simulation_duration");
  std::string command = "gazebo --world=" + world_model + "--max_sim_time " +
                        std::to_string(secs);

  system(command.c_str());
}