cmake_minimum_required(VERSION 3.0)
project(pd_guidance_test)

enable_testing()
find_package(GTest CONFIG REQUIRED COMPONENTS GTest GMock)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable languages
enable_language(CXX)
message("Compiler: ${CMAKE_CXX_COMPILER}")

# Define the source files
add_executable(${PROJECT_NAME} 
               guidance_test.cpp)

# Create an executable
link_directories(${GTEST_LIBRARY} -pthread)
target_link_libraries(${PROJECT_NAME} 
                      ${GTEST_LIBRARY}
                      PRIVATE gtest_main gtest gmock
                      ${CMAKE_CURRENT_SOURCE_DIR}/../../../adapters/build/libadapters.a
                      #${CMAKE_CURRENT_SOURCE_DIR}/../build/libguidance.a
                      )

# Set the build folder
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Set the include directories
target_include_directories(${PROJECT_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../../../..
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../interfaces
    ${GTEST_INCLUDE_DIR}
    /usr/src/gmock/include/
)

# Set the library output directory
set_target_properties(${PROJECT_NAME} 
	PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/
)