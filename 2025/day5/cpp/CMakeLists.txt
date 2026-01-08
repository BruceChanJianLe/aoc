cmake_minimum_required(VERSION 3.5)
project(day5)

set(CMAKE_CXX_STANDARD 23)

add_executable(day5_part1 day5_part1.cpp)
target_include_directories(day5_part1 PUBLIC ../../common)

add_test(NAME day5_part1 COMMAND day5_part1)
set_tests_properties(day5_part1 PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
