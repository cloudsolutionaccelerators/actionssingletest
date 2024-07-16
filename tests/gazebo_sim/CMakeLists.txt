cmake_minimum_required(VERSION 3.0)
project(gazebo_sim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable languages
enable_language(CXX)
message("Compiler: ${CMAKE_CXX_COMPILER}")

# Define the source files
add_executable(${PROJECT_NAME}
               scenario_builder.cpp)

# Create a static library
target_link_libraries(${PROJECT_NAME} stdc++
                      ${CMAKE_CURRENT_SOURCE_DIR}/../agv_container/build/libagv_sim_container.a
					  ${CMAKE_CURRENT_SOURCE_DIR}/../../modules/pi/guidance/build/libpi_guidance.a
					  ${CMAKE_CURRENT_SOURCE_DIR}/../../modules/pi/odometry/build/libpi_odometry.a
					  ${CMAKE_CURRENT_SOURCE_DIR}/../../modules/pi/sensor_fusion/build/libpi_sensor_fusion.a
					  ${CMAKE_CURRENT_SOURCE_DIR}/../../modules/pi/motion_control/build/libpi_motion_control.a)
include_directories(${CMAKE_CLANGXX_INCLUDE_DIR})

# Set the build folder
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Set the include directories
target_include_directories(${PROJECT_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../../interfaces
	${CMAKE_CURRENT_SOURCE_DIR}/../agv_container
)

# set local and global scope. 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror -pedantic")
add_compile_options(-std=c++17 -Wall -Wextra -Werror -pedantic)

# Set the library output directory
set_target_properties(${PROJECT_NAME} 
	PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/
)