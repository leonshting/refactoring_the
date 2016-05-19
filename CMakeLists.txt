cmake_minimum_required(VERSION 3.3)
project(stress_rec_refactored)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp init_data.cpp init_data.h data_points.cpp data_points.h subfield_rec_solver.cpp subfield_rec_solver.h settings.cpp settings.h useful.h useful.cpp output.cpp output.h FinalPSolver.cpp FinalPSolver.h d3_zone.cpp d3_zone.h layer.cpp layer.h pressures.cpp pressures.h border.cpp border.h)
add_executable(stress_rec_refactored ${SOURCE_FILES})