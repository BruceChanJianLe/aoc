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

    // 1. Adjust to valid number range (even number of digits)
    // round up to nearest even number of digits for lo limit
    // e.g. 123 -> 1000
    if (lo_str.size() % 2 != 0) {
      lo_str = "1" + std::string(lo_str.size(), '0');
    }

    // round down to nearest even number of digits for hi limit
    // e.g. 321 -> 99
    if (hi_str.size() % 2 != 0) {
      hi_str = std::string(hi_str.size() - 1, '9');
    }

    auto lo_int{std::stol(lo_str)};
    auto hi_int{std::stol(hi_str)};

    // invalid number range
    if (lo_int > hi_int) continue;

    // 2. Check if first repeated number is in range
    // split lo limit to half then check if the repeated first half is in range
    // e.g. if lo limit is 1234, then 1212 is out of range
    auto half_int = std::stol(lo_str.substr(0, lo_str.size() / 2));
    auto half_str{std::to_string(half_int)};
    auto repeated_int{std::stol(half_str + half_str)};
    if (repeated_int >= lo_int && repeated_int <= hi_int) {
        sum += repeated_int;
    }

    // do nothing if the first half of lo limit is equal first half of hi limit
    // e.g. 1234 -> 1256
    if (half_int == std::stol(hi_str.substr(0, hi_str.size() / 2))) continue;

    // 3. Iterate from (first half + 1) of lo limit to (first half - 1) of hi limit 
    // Sum all the repeated numbers
    // e.g. for 1234 -> 5678, iterate from 13 -> 55
    for (auto i = half_int + 1; i < std::stol(hi_str.substr(0, hi_str.size() / 2)); ++i) {
      half_str = std::to_string(i);
      repeated_int = std::stol(half_str + half_str);
      sum += repeated_int;
    }

    // 4. Check if last repeated number is in range
    // e.g. for 1234 -> 5678, 5656 is within range
    half_int = std::stol(hi_str.substr(0, hi_str.size() / 2));
    half_str = std::to_string(half_int);
    repeated_int = std::stol(half_str + half_str);
    if (repeated_int <= hi_int) {
      sum += repeated_int;
    }
  }
  std::cout << "sum: " << sum << std::endl;

  return 0;
}
