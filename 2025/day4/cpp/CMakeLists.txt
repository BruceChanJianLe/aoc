cmake_minimum_required(VERSION 3.5)
project(day4)

set(CMAKE_CXX_STANDARD 23)

add_executable(day4_part1 day4_part1.cpp)
target_include_directories(day4_part1 PUBLIC ../../common)
add_executable(day4_part2 day4_part2.cpp)
target_include_directories(day4_part2 PUBLIC ../../common)

add_test(NAME day4_part1 COMMAND day4_part1)
set_tests_properties(day4_part1 PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_test(NAME day4_part2 COMMAND day4_part2)
set_tests_properties(day4_part2 PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# cjl part1
add_executable(day4_part1_cjl day4_part1_cjl.cpp)
target_include_directories(day4_part1_cjl PUBLIC ../../common)
target_link_libraries(day4_part1_cjl PRIVATE mdspan)

add_test(NAME day4_part1_cjl_test COMMAND day4_part1_cjl)
set_tests_properties(day4_part1_cjl_test PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_test(NAME day4_part1_cjl COMMAND day4_part1_cjl cjl)
set_tests_properties(day4_part1_cjl PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# cjl part2
add_executable(day4_part2_cjl day4_part2_cjl.cpp)
target_include_directories(day4_part2_cjl PUBLIC ../../common)
target_link_libraries(day4_part2_cjl PRIVATE mdspan)

add_test(NAME day4_part2_cjl_test COMMAND day4_part2_cjl)
set_tests_properties(day4_part2_cjl_test PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_test(NAME day4_part2_cjl COMMAND day4_part2_cjl cjl)
set_tests_properties(day4_part2_cjl PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
