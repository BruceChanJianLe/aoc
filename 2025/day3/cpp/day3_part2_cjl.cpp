#include "input_reader.hpp"
#include <cstdlib>
#include <string>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  static const char* default_input = "test";

  std::string_view input_path;
  if (argc != 2) {
    input_path = default_input;
  } else if (argc == 2){
    input_path = argv[1];
  }

  auto inputs = aoc::InputReader::get_input<std::string>(input_path);

  long long results{};
  const auto input_size = inputs.front().size() - 1;
  for (const auto& input : inputs) {
    std::vector<int> stack;
    for (int i = 0; i < std::ssize(input); ++i) {
      auto curr_val = input[i] - '0';
      // condition1: Ensure we have enough choices left to add into the stack
      // condtiion2: Ensure a value to be compare with curr_val
      // condition3: Only pop the stack if curr_val is strictly larger
      while ((input_size - i >= 12 - stack.size()) && stack.size() > 0 && curr_val > stack.back()) {
        stack.pop_back();
      }
      // only add it if stack is less than 12 digit
      if (stack.size() < 12) {
        stack.push_back(curr_val);
      }
    }

    // Add to results
    long long step = 1;
    for (auto it = stack.crbegin(); it != stack.crend(); ++it) {
      results += *it * step;
      step *= 10;
    }
  }

  std::cout << "Result: " << results << std::endl;

  return EXIT_SUCCESS;
}
