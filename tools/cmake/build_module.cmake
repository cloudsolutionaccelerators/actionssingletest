
function(build_module SOURCE LIBRARIES)
  message("CMake version: ${CMAKE_VERSION}")

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

  # Enable languages
  enable_language(CXX)
  message("Compiler: ${CMAKE_CXX_COMPILER}")

  # Define the source files
  set(SOURCES ${SOURCE})

  add_custom_target(
  clang-tidy
  COMMAND clang-tidy
  ${PROJECT_SOURCE_DIR}
)

  # add clang-tidy
  clang_tidy(
    ${PROJECT_NAME}
    "-checks=cppcoreguidelines-*, modernize-*, performance-*, readability-*"
    "-std=c++17"
  )

  # Create a static library
  target_link_libraries(${PROJECT_NAME} ${LIBRARIES} stdc++)
  include_directories(${CMAKE_CLANGXX_INCLUDE_DIR})

  # Set the build folder
  set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_LIST_DIR}/build)

  # Set the include directories
  target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../interfaces
  )

  # Set local and global scope
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror -pedantic")
  add_compile_options(-std=c++17 -Wall -Wextra -Werror -pedantic)

  # Set the library output directory
  set_target_properties(${PROJECT_NAME} 
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/
  )

export(TARGETS ${PROJECT_NAME} FILE "build_module.cmake")

endfunction()
