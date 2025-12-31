#include "input_reader.hpp"
#include <cstdint>
#include <ranges>

int main (int argc, char *argv[])
{
  static const char* default_input = "test";

  std::string_view input;
  if (argc != 2) {
    input = default_input;
  } else if (argc == 2){
    input = argv[1];
  }

  auto inputs = aoc::InputReader::get_input<std::string>(input);
  uint64_t result{};

  for (const auto& input : inputs) {
    // Store the largest seen from left to right
    std::vector<int> left{};
    int max_seen{};
    for (const auto& c : input) {
      max_seen = std::max(max_seen, c - '0');
      left.emplace_back(max_seen);
    }

    // Store the largest seen from right to left
    std::vector<int> right(input.size());
    // Reuse max_seen variable hence reset to 0
    max_seen = 0;
    for (const auto& [c, rc] : std::views::zip(input, right) | std::views::reverse) {
      max_seen = std::max(max_seen, c - '0');
      rc = max_seen;
    }

    // Go through the left and right vector to form the numbers
    // Compare the number for and retain the max seen
    // Reuse max_seen variable hence reset to 0
    max_seen = 0;
    for (auto i = 0, j = 1; j < (int)input.size(); ++i, ++j) {
      max_seen = std::max(max_seen, left[i] * 10 + right[j]);
    }

    result += max_seen;
    // std::cout << input << ": " << max_seen << " ..." << result << std::endl;
  }

  std::cout << "result: " << result << std::endl;
  return 0;
}
