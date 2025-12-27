cmake_minimum_required(VERSION 3.5)
project(day2)

add_executable(day2_part1 day2_part1.cpp)
target_include_directories(day2_part1 PUBLIC ../../common)

add_test(NAME day2_part1_cjl COMMAND day2_part1 cjl)
add_test(NAME day2_part1 COMMAND day2_part1)
set_tests_properties(day2_part1 PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(day2_part2 day2_part2.cpp)
target_include_directories(day2_part2 PUBLIC ../../common)

add_test(NAME day2_part2_cjl COMMAND day2_part2 cjl)
add_test(NAME day2_part2 COMMAND day2_part2)
set_tests_properties(day2_part2 PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
