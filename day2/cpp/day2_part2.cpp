#include <cstdint>
#include <iostream>
#include <numeric>
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

// First attemp: reuse the solution from part1, but it does scale for part2
// Because in the case of word_size == 1, 1001 would be 1^0^0^1 the same
// as 1010, which is, of course, wrong
inline void is_valid(uint64_t &result, uint64_t num, std::string_view sv) {
  const auto length = sv.size();
  const auto half_length = sv.size() / 2;

  for (const auto word_size : std::ranges::iota_view(1u, half_length) | std::views::reverse) {
    // Sanity check
    if (sv.size() % word_size != 0) continue;
    const auto word = sv.size() / word_size;

    uint64_t val{}, cur_val{};
    if (word_size == 1) {
      aoc::convert(sv.substr(0, word_size), val);
      for (uint64_t i = 0; i * word_size < length; ++i) {
        if (aoc::convert(sv.substr(i * word_size, word_size), cur_val)) {
          if (val != cur_val) break;
        }
      }
      // if never break
      result += num;
    } else {
      for (uint64_t i = 0; i * word_size < length; ++i) {
        if (aoc::convert(sv.substr(i * word_size, word_size), cur_val)) {
          val ^= cur_val;
        }
      }
      if ((word % 2 == 0) && val == 0) {
        std::cout << num << ", " << cur_val << std::endl;
        result += num;
        break;
      } else if ((word % 2 != 0)) {
        aoc::convert(sv.substr(0, word_size), cur_val);
        if (cur_val == val) {
          std::cout << num << ", " << cur_val << std::endl;
          result += num;
          break;
        }
      }
    }
  }
}

inline void second_attempt(std::string_view sv, uint64_t num, uint64_t& result) {
  const auto length_half = sv.size() / 2;
  const auto length_full = sv.size();
  // std::cout << "Running checks on: " << sv << '\n' << std::endl;
  // loops of chunk view
  for (const auto word_size : std::ranges::iota_view(1u, length_half + 1u)) {
    // Sanity check, whether can break into equal chuncks
    if (length_full % word_size != 0) continue;

    std::string_view prev_view{};
    bool is_valid{true};
    for (const auto curr_view : std::ranges::chunk_view(sv, word_size)) {
      // std::cout << std::string_view{curr_view} << ", ";
      // Always store the first view
      if (prev_view.empty()) {
        prev_view = std::string_view{curr_view};
        continue;
      } 

      for (const auto [lp, rp] : std::ranges::zip_view(prev_view, curr_view)) {
        // Invalid ID
        if (lp != rp) {
          // std::cout << " this is not valid... ";
          is_valid = false;
          break;
        }
      }
      // Stop checking if its a valid id
      if (!is_valid) break;
    }
    // Valid ID, add to result and stop checking
    if (is_valid) {
      // std::cout << sv << " VALID ID\n" << std::endl;
      result += num;
      break;
    }
    // std::cout << std::endl;
  }
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
        // First attempt -> failed
        // is_valid(result, num, snum);
        // Second attempt
        second_attempt(snum, num, result);
      }
      // std::cout << std::endl;
    }
  }

  std::cout << "result: " << result;

  return 0;
}
