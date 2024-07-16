# Sensor Fusion

## Introduction

The sensor fusion component provides the localization
functionality within the product which feeds into
the guidance of the system.

## Usage

1. From the main folder run `cmake -S . -B build`
2. Generate the build using `cmake --build build`
3. Clang-format use the command below:
   find ./ -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i

## Features

* Implements the main interfaces PI_Sensor_Fusion_I
* and PI_Sensor_Fusion_S

## Requirements

* cmake, clang, g++ or gcc

## License

None.

## Contact

Author: Mahendra Ghimirey
