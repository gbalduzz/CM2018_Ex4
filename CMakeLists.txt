cmake_minimum_required(VERSION 3.10)
project(CMSolver)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(solve src/solve.cpp src/second_order_solver.cpp src/json11.cpp src/analytic_period.cpp)
target_compile_definitions(solve PUBLIC SOURCE_DIR="${PROJECT_SOURCE_DIR}")
