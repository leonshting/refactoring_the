cmake_minimum_required(VERSION 3.3)
project(stress_rec_refactored)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp init_data.cpp init_data.h data_points.cpp data_points.h subfield_rec_solver.cpp subfield_rec_solver.h settings.cpp settings.h useful_linear_algebra.h)
add_executable(stress_rec_refactored ${SOURCE_FILES})