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

  std::string_view input_path;
  if (argc != 2) {
    input_path = default_input;
  } else if (argc == 2){
    input_path = argv[1];
  }

  auto inputs = aoc::InputReader::get_input<std::string>(input_path);

  int sum{0};
  for (const auto input : inputs) {
    std::cout << std::string_view(input.begin(), input.end()) << std::endl;

    auto first{input.begin()};
    auto second{first + 1};
    auto curr{second};
    for (int i = 1; i < input.size(); ++i, ++curr) {
      if (*curr > *first && curr + 1 != input.end()) {
        first = curr;
        second = first + 1;
      }
      else if (*curr > *second) {
        second = curr;
      }
    }

    sum += (*first - '0') * 10 + (*second - '0');
  }
  std::cout << "sum: " << sum << std::endl;

  return 0;
}
