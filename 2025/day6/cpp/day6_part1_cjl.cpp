#include <execution>
#include <numeric>
#include <functional>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
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

  std::vector<long> maths;
  maths.reserve(inputs.size() - 1);
  std::vector<char> ops;

  for (const auto& input : inputs) {
    std::vector<long long> math;
    std::istringstream iss(input);
    std::string temp;
    while (iss >> temp) {
      if (temp.compare("+") == 0 || temp.compare("*") == 0) {
        ops.push_back(temp.front());
      } else {
        maths.emplace_back(std::stoll(temp));
      }
    }
  }

  // Stride
  auto stride = ops.size();
  // Start indexes
  std::vector<std::size_t> indexes(ops.size());
  std::iota(indexes.begin(), indexes.end(), 0u);

  long long results = std::transform_reduce(
      std::execution::par_unseq,
      indexes.begin(),
      indexes.end(),
      0L,
      std::plus<>(),
      [&ops, &stride, &maths](const auto& index) -> long long {
        long long result{(ops[index] == '+' ? 0L : 1L)};
        auto batch = maths
          | std::views::drop(index)
          | std::views::stride(stride);

        if (ops[index] == '+') {
          for (const auto& val : batch) {
            result += val;
          }
        } else {
          for (const auto& val : batch) {
            result *= val;
          }
        }

        return result;
      }
      );

  std::cout << "Results: " << results << std::endl;
  return 0;
}
