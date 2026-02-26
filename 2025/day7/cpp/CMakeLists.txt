cmake_minimum_required(VERSION 3.5)
project(day7)

set(CMAKE_CXX_STANDARD 23)

add_executable(day7_part1 day7_part1.cpp)
target_include_directories(day7_part1 PUBLIC ../../common)
add_executable(day7_part2 day7_part2.cpp)
target_include_directories(day7_part2 PUBLIC ../../common)

add_test(NAME day7_part1 COMMAND day7_part1)
set_tests_properties(day7_part1 PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_test(NAME day7_part2 COMMAND day7_part2)
set_tests_properties(day7_part2 PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# cjl part1
add_executable(day7_part1_cjl day7_part1_cjl.cpp)
target_include_directories(day7_part1_cjl PUBLIC ../../common)
target_link_libraries(day7_part1_cjl PRIVATE TBB::tbb)

add_test(NAME day7_part1_cjl_test COMMAND day7_part1_cjl)
set_tests_properties(day7_part1_cjl_test PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_test(NAME day7_part1_cjl COMMAND day7_part1_cjl cjl)
set_tests_properties(day7_part1_cjl PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# cjl part2
add_executable(day7_part2_cjl day7_part2_cjl.cpp)
target_include_directories(day7_part2_cjl PUBLIC ../../common)
target_link_libraries(day7_part2_cjl PRIVATE TBB::tbb mdspan)

add_test(NAME day7_part2_cjl_test COMMAND day7_part2_cjl)
set_tests_properties(day7_part2_cjl_test PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_test(NAME day7_part2_cjl COMMAND day7_part2_cjl cjl)
set_tests_properties(day7_part2_cjl PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
