#include <iostream>
#include <sstream>
#include <vector>

#include "input_reader.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  static const char* default_input = "test";

  std::string_view input_path;
  if (argc != 2) {
    input_path = default_input;
  } else if (argc == 2){
    input_path = argv[1];
  }

  auto inputs = aoc::InputReader::get_input<std::string>(input_path);
  auto rows = inputs.size();
  auto cols = inputs.front().size();
  int mid = cols / 2;
  inputs[1][mid] = '|';
  for (int r = 1; r < rows - 1; ++r) {
    for (int c = 0; c < cols - 1; ++c) {
      if (inputs[r-1][c] == '|') {
        if (inputs[r][c] == '^') {
          inputs[r][c-1] = '|';
          inputs[r][c+1] = '|';
        }
        else {
          inputs[r][c] = '|';
        }
      }
    }
  }

  std::vector<std::vector<long>> num_paths{rows, std::vector<long>(cols, 0)};
  num_paths[1][mid] = 1;
  int start_c{mid};
  int end_c{mid};
  for (int r = 2; r < rows - 1; r += 2, --start_c, ++end_c) {
    for (int c = start_c; c <= end_c; c += 2) {
      if (inputs[r][c] == '^' && inputs[r-1][c] == '|') {
        if (c == start_c) {
            num_paths[r+1][c-1] = num_paths[r-1][c];
        }
        num_paths[r+1][c+1] = num_paths[r-1][c];
        if (c + 2 <= end_c) {
          num_paths[r+1][c+1] += num_paths[r-1][c+1];
          if (inputs[r][c+2] == '^' && inputs[r-1][c+2] == '|') {
            num_paths[r+1][c+1] += num_paths[r-1][c+2];
          }
        }
      }
      else {
        num_paths[r+1][c] = num_paths[r-1][c];
        if (c + 2 <= end_c) {
          num_paths[r+1][c+1] = num_paths[r-1][c+1];
          if (inputs[r][c+2] == '^' && inputs[r-1][c+2] == '|') {
            num_paths[r+1][c+1] += num_paths[r-1][c+2];
          }
        }
      }
    }
  }

  long count{0};
  for (int i = 0; i < num_paths.back().size(); ++i) {
    count += num_paths.back()[i];
  }
  std::cout << "count: " << count << std::endl;

  return 0;
}
