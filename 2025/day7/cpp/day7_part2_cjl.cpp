#include <iostream>
#include <ranges>
#include <vector>
#include <span>

#include "input_reader.hpp"

// Too slow
void count_timeline(std::span<std::string> inputs,
    const int pos,
    int& results) {
  // Base cases
  if (inputs.size() == 1) {
    ++results;
    return;
  }

  // Hit splitter
  if (inputs.front()[pos] == '^') {
    // Left split
    count_timeline(inputs.subspan(1), pos - 1, results);
    // Right split
    count_timeline(inputs.subspan(1), pos + 1, results);
  } else {
    // Walk one level down
    count_timeline(inputs.subspan(1), pos, results);
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  static const char* default_input = "test";

  std::string_view input_path;
  if (argc != 2) {
    input_path = default_input;
  } else if (argc == 2){
    input_path = argv[1];
  }

  auto inputs = aoc::InputReader::get_input<std::string>(input_path);
  std::vector result(inputs.front().size(), 1LL);

  for (const auto &input : std::ranges::reverse_view(inputs)) {
    for (auto i = 0uz; i < input.size(); ++i) {
      if (input[i] == '^') {
        result[i] = result[i - 1] + result[i + 1];
      }
    }
  }
  auto start_index = inputs.front().find_first_of('S');

  std::cout << "Results: " << result[start_index] << std::endl;
  return 0;
}
