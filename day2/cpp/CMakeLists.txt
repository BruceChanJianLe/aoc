cmake_minimum_required(VERSION 3.5)
project(day2)

set(CMAKE_CXX_STANDARD 23)

add_executable(day2_part1 day2_part1.cpp)
target_include_directories(day2_part1 PUBLIC ../../common)
add_executable(day2_part2 day2_part2.cpp)
target_include_directories(day2_part2 PUBLIC ../../common)

add_executable(day2_part1_brina day2_part1_brina.cpp)
target_include_directories(day2_part1_brina PUBLIC ../../common)
add_executable(day2_part2_brina day2_part2_brina.cpp)
target_include_directories(day2_part2_brina PUBLIC ../../common)

add_test(NAME day2_part1_cjl COMMAND day2_part1 cjl)
add_test(NAME day2_part1_brina COMMAND day2_part1_brina brina)
add_test(NAME day2_part1 COMMAND day2_part1)
set_tests_properties(day2_part1 PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set_tests_properties(day2_part1_cjl PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set_tests_properties(day2_part1_brina PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_test(NAME day2_part2_cjl COMMAND day2_part2 cjl)
add_test(NAME day2_part2_brina COMMAND day2_part2_brina brina)
add_test(NAME day2_part2 COMMAND day2_part2)
set_tests_properties(day2_part2 PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set_tests_properties(day2_part2_cjl PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set_tests_properties(day2_part2_brina PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
