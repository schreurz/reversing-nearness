# CMakeList.txt : CMake project for reversing-nearness, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (reversing-nearness "reversing-nearness.cpp" "reversing-nearness.h" "CGeneticAlgorithm.cpp" "CGeneticAlgorithm.h" "CGrid.cpp" "CGrid.h")

# TODO: Add tests and install targets if needed
