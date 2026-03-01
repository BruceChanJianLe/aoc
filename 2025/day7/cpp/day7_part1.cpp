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

  int count{0};
  for (int r = 1; r < inputs.size(); ++r) {
    for (int c = 0; c < inputs.front().size(); ++c) {
      if (inputs[r-1][c] == 'S' || inputs[r-1][c] == '|') {
        if (inputs[r][c] == '^') {
          inputs[r][c-1] = '|';
          inputs[r][c+1] = '|';
          count++;
        }
        else {
          inputs[r][c] = '|';
        }
      }
    }
  }

  std::cout << "count: " << count << std::endl;

  return 0;
}
