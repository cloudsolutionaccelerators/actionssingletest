# TCBSD

## Introduction

This repo contains the application and libraries for tcbsd repo.

## Usage

* The cmake commands for each individual modules are listed in 
  the corresponding folders along with the tests.

  1) Following command will recursively create a build folder.

     find ./ -iname 'CMakeLists.txt' | xargs cmake -S . -B build

    Or alternatively do the following in each folders.
    cmake -S . -B build
    cmake --build build
  
  2) Run the clang-format to clean up the formatting using the
     following command:

    `git status | find . -name '*.cpp' -o -name '*.h' | xargs clang-format -i`

## Features

* None

## Requirements

* cmake, clang, g++, gcc, boost, clang-format, clang-tidy, eigen, gtest, gmock
  llvm, python3, pytest, gazebo harmony, matplotlib, seaborn. 

## License

None.

## Contact

None.

