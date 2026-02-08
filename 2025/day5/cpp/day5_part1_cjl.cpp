#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>
#include <execution>

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

  std::vector<long long> lows, highs;
  std::vector<long long> ingredients;

  for (const auto& input : inputs) {
    if (auto pos = input.find('-'); pos == std::string::npos) {
      if (!input.empty()) {
        ingredients.emplace_back(std::stoll(input));
      }
    } else {
      lows.emplace_back(std::stoll(input.substr(0, pos)));
      highs.emplace_back(std::stoll(input.substr(pos + 1)));
    }
  }

  long long results = std::transform_reduce(
      std::execution::par_unseq,
      ingredients.begin(),
      ingredients.end(),
      0L,
      std::plus<>(),
      [&](const auto& input) -> long {
        auto bounds = std::ranges::zip_view(lows, highs);
        bool fall_within = std::ranges::any_of(
            bounds.begin(), bounds.end(),
            [&input](const auto& bound) {
            auto [lo, hi] = bound;
            return (lo <= input && input <= hi);
        });

        return fall_within ? 1L : 0L;
      });

    std::cout << "Result: " << results << std::endl;

  return 0;
}
