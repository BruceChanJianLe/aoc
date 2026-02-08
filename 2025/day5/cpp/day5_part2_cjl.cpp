#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>
#include <execution>

#include "input_reader.hpp"

struct Pairs { long long lo, hi; };

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  static const char* default_input = "test";

  std::string_view input_path;
  if (argc != 2) {
    input_path = default_input;
  } else if (argc == 2){
    input_path = argv[1];
  }

  auto inputs = aoc::InputReader::get_input<std::string>(input_path);

  std::vector<Pairs> pairs;

  for (const auto& input : inputs) {
    if (auto pos = input.find('-'); pos != std::string::npos) {
      pairs.emplace_back(Pairs{std::stoll(input.substr(0, pos)), std::stoll(input.substr(pos + 1))});
    }
  }

  std::sort(pairs.begin(), pairs.end(),
      [](const auto& p1, const auto& p2) { return p1.lo < p2.lo; });

  // for (const auto& pair : pairs) {
  //   std::cout << pair.lo << ", " << pair.hi << std::endl;
  // }

  std::vector<Pairs> results{pairs.front()};

    std::for_each(
      pairs.begin(),
      pairs.end(),
      [&results](const auto& pair) {
        auto& [lo, hi] = results.back();
        const auto& [clo, chi] = pair;
        if (lo <= clo && clo <= hi) {
          if (chi > hi) {
            hi = chi;
          }
        } else {
          results.push_back(pair);
        }
      });

    long long result = std::transform_reduce(
        std::execution::par_unseq,
        results.begin(),
        results.end(),
        0L,
        std::plus<>(),
        [](const auto& result) -> long {
          return result.hi - result.lo + 1;
        }
        );

    std::cout << "Result: " << result << std::endl;

  return 0;
}
