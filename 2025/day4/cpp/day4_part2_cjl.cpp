#include <array>
#include <cstdlib>
#include <iostream>
#include "mdspan/mdspan.hpp"
#include <stack>

#include "input_reader.hpp"

struct Step { int row, col; };

static constexpr std::array<Step, 8> walks {{
  {-1, -1}, {-1,  0}, {-1,  1},
  { 0, -1},           { 0,  1},
  { 1, -1}, { 1,  0}, { 1,  1}
}};

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  static const char* default_input = "test";

  std::string_view input_path;
  if (argc != 2) {
    input_path = default_input;
  } else if (argc == 2){
    input_path = argv[1];
  }

  // Please ensure you know the size before using
  static constexpr auto array_size = 140 * 140;
  auto inputs = aoc::InputReader::get_input<char, array_size>(input_path);

  Kokkos::mdspan<char, Kokkos::extents<std::size_t, 140, 140>> grid(inputs.data());
  long long int results{};
  std::stack<Step> steps{};

  do {
    // Apply steps
    while (!steps.empty()) {
      auto step = steps.top();
      grid[step.row, step.col] = '.';
      steps.pop();
    }

    for (int row = 0; row < (int)grid.extent(0); ++row) {
      for (int col = 0; col < (int)grid.extent(1); ++col) {
        // Skip if it's not an @
        if (grid[row, col] != '@') continue;

        int result{};
        for (const auto& walk : walks) {

          Step step {row + walk.row, col + walk.col};
          // Boundary checking
          if (step.row >= 0 && step.row < 140 && step.col >= 0 && step.col < 140) {
            if (grid[step.row, step.col] == '@') {
              ++result;
            }
          }
        }
        if (result < 4) {
          ++results;
          steps.emplace(row, col);
        }
      }
    }
  } while (!steps.empty());

  std::cout << "Result: " << results << std::endl;

  return EXIT_SUCCESS;
}
