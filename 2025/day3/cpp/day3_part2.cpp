#include <fstream>
#include <iostream>
#include <ranges>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>
#include <memory>

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

  long sum{0l};
  for (const auto& input : inputs) {
    std::vector<std::string::const_iterator> ptrs(12, input.begin());
    for (int i = 0; i < 12; ++i) {
      ptrs[i] += i;
    }

    auto curr{ptrs[1]};
    for (int i = 1; i < input.size() && ptrs.back() + 1 != input.end(); ++i, ++curr) {
      for (int j = 0; j < 12; ++j) {
        if (ptrs[j] == curr) break;
        if (*curr > *ptrs[j] && i + (11 - j) < input.size()) {
          ptrs[j] = curr;
          for (int k = j + 1; k < 12; ++k) {
            ptrs[k] = curr + k - j;
          }
          break;
        }
      }
    }

    long joltage{0l};
    for (int i = 0; i < 12; ++i) {
      joltage = joltage * 10 + (*ptrs[i] - '0');
    }
    sum += joltage;
  }
  std::cout << "sum: " << sum << std::endl;

  return 0;
}
