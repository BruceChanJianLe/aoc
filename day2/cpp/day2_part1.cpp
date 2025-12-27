#include <cstdint>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

#include "input_reader.hpp"


inline std::string_view from_int(const uint64_t value, char* buffer, std::size_t size) {
  auto [ptr, ec] = std::to_chars(buffer, buffer + size, value);

  if (ec == std::errc{}) {
    return std::string_view(buffer, ptr - buffer);
  }

  return {};
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  static const char* default_input = "test";

  std::string_view input;
  if (argc != 2) {
    input = default_input;
  } else if (argc == 2){
    input = argv[1];
  }

  auto inputs = aoc::InputReader::get_input<std::string>(input);

  char buf[128];
  uint64_t result{};
  for (const auto input : inputs.front() | std::views::split(',')) {
    std::string_view sv{input};
    // std::cout << sv << std::endl;
    auto pos = sv.find('-');
    if (uint64_t range_start, range_end;
        aoc::convert(sv.substr(0, pos), range_start)
        && aoc::convert(sv.substr(pos + 1), range_end)) {
      for (uint64_t num = range_start; num <= range_end; ++num) {
        auto snum = from_int(num, buf, sizeof buf);
        // Sanity check
        if (snum.size() % 2 != 0) continue;
        const auto mid = snum.size() / 2;
        if (uint64_t left, right;
            aoc::convert(snum.substr(0, mid), left)
            && aoc::convert(snum.substr(mid), right)) {
          // std:: << left << ":" << right << "[" << snum.size() << "], ";
          if ((0^left^right) == 0) {
            result += num;
          }
        }
      }
      // std::cout << std::endl;
    }
  }

  std::cout << "result: " << result;

  return 0;
}
