cmake_minimum_required(VERSION 3.5)
project(day1)

add_executable(day1_part1 day1_part1.cpp)
add_executable(day1_part2 day1_part2.cpp)

add_test(NAME day1_part1 COMMAND day1_part1)
set_tests_properties(day1_part1 PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_test(NAME day1_part2 COMMAND day1_part2)
set_tests_properties(day1_part2 PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
