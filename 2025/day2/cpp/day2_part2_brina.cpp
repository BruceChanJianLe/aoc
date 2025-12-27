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

  long sum = 0L;
  for (const auto input : inputs.front() | std::views::split(',')) {
    std::cout << std::string_view(input.begin(), input.end()) << std::endl;

    std::string token{input.begin(), input.end()};
    auto pos{token.find('-')};
    auto lo_str{token.substr(0, pos)};
    auto hi_str{token.substr(pos + 1)};

    // 1. Iterate through number of digits possible
    // e.g. for range 1234 -> 5678, iterate until 2
    auto max_size = hi_str.size() / 2;
    max_size = max_size % 2 == 0 ? max_size : max_size + 1;
    auto max_pattern = std::stol(hi_str.substr(0, max_size));
    for (int i = 0; i < hi_str.size() / 2; ++i) {
      auto lo_pattern = "1" + std::string(i, '0'); // digit pattern 1(0...)
      auto hi_pattern = "9" + std::string(i, '9'); // digit pattern 9(9...)

      // 2. Iterate from lo to hi digit pattern
      // e.g. 1 -> 9, then 10 -> 99
      auto end_pattern = std::min(std::stol(hi_pattern), max_pattern);
      for (int j = std::stol(lo_pattern); j <= end_pattern; ++j) {
        // divisible by 11(1...)
        if (i > 0 && j % std::stol(std::string(lo_pattern.size(), '1')) == 0) continue;

        // 3. Iterate from lo str size to hi str size 
        // e.g. 4 -> 4
        for (int k = std::max(2, int(lo_str.size())); k <= hi_str.size(); ++k) {
          if (k % std::to_string(j).size() != 0) continue;

          // avoid double counting
          // e.g. ignore 2424+2424 since 24+24+24+24 is already considered
          int rep = k / std::to_string(j).size();
          if (i > 0 && rep > 3 && rep % 2 == 0) continue;

          // create the string from repeated pattern
          std::string rep_str;
          rep_str.reserve(k);
          for (int n = 0; n < rep; ++n) {
            rep_str += std::to_string(j);
          }

          // check result within range
          auto res = std::stol(rep_str);
          if (res > std::stol(hi_str)) break;
          if (res >= std::stol(lo_str) && res <= std::stol(hi_str)) {
            sum += res;
          }
        }
      }
    }
  }
  std::cout << "sum: " << sum << std::endl;

  return 0;
}
