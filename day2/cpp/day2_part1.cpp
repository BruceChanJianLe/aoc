#include <fstream>
#include <iostream>
#include <ranges>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>

#include "input_reader.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  static const char* default_input = "test";

  std::string_view input;
  if (argc != 2) {
    input = default_input;
  } else if (argc == 2){
    input = argv[1];
  }

  auto inputs = aoc::InputReader::get_input<std::string>(input);

  for (const auto input : inputs.front() | std::views::split(',')) {
    std::cout << std::string_view(input.begin(), input.end()) << std::endl;
  }

  return 0;
}
