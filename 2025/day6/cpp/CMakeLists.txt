cmake_minimum_required(VERSION 3.5)
project(day6)

set(CMAKE_CXX_STANDARD 23)

add_executable(day6_part1 day6_part1.cpp)
target_include_directories(day6_part1 PUBLIC ../../common)
add_executable(day6_part2 day6_part2.cpp)
target_include_directories(day6_part2 PUBLIC ../../common)

add_test(NAME day6_part1 COMMAND day6_part1)
set_tests_properties(day6_part1 PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_test(NAME day6_part2 COMMAND day6_part2)
set_tests_properties(day6_part2 PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
