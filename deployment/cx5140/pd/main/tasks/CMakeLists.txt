cmake_minimum_required(VERSION 3.10)
project(tasks)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable languages
enable_language(CXX)
message("Compiler: ${CMAKE_CXX_COMPILER}")

# Define the source files
set(SOURCES
  30ms_task_periodic.cpp
)

# Create a static library
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} stdc++)
include_directories(${CMAKE_CLANGXX_INCLUDE_DIR})

# Set the build folder
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Set the include directories
target_include_directories(${PROJECT_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../../..
)

# set local and global scope. 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror -pedantic")
add_compile_options(-std=c++17 -Wall -Wextra -Werror -pedantic)

# Set the library output directory
set_target_properties(${PROJECT_NAME} 
	PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/
)