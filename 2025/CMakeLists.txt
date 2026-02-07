cmake_minimum_required(VERSION 3.5)
project(aoc2025)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++23
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Use ctest
enable_testing()

include(FetchContent)

# Make mdspan available project wide
FetchContent_Declare(
  kokkos_mdspan
  GIT_REPOSITORY https://github.com/kokkos/mdspan.git
  GIT_TAG stable
)
FetchContent_MakeAvailable(kokkos_mdspan)

# Add day1
add_subdirectory(day1/cpp)

# Add day2
add_subdirectory(day2/cpp)

# Add day3
add_subdirectory(day3/cpp)

# Add day4
add_subdirectory(day4/cpp)

# Add day5
add_subdirectory(day5/cpp)

# Add day6
add_subdirectory(day6/cpp)
