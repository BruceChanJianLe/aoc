#include <execution>
#include <numeric>
#include <functional>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <utility>
#include <vector>
#include <format>


#include "input_reader.hpp"

// A template based
template <std::size_t... Indexes>
long long process(const std::vector<std::string>& inputs, std::index_sequence<Indexes...>) {
  long long results{};

  // zip all the strings to access at the same time (in reverse order)
  auto zipped = std::views::zip(inputs[Indexes]...) | std::views::reverse;

  std::vector<std::string> numbers;
  for (auto&& char_tuple : zipped) {
    std::string curr_str;

    std::apply([&curr_str](auto... chars){ (curr_str.push_back(chars), ...); }, char_tuple);

    // Skip if it only contains spaces
    if (curr_str.find_first_not_of(" ") == std::string::npos) continue;

    if (curr_str.back() == '+' || curr_str.back() == '*') {
      // Flag for plus operation (need not check curr_str.back all the time)
      auto is_plus = curr_str.back() == '+' ? true : false;
      auto result = std::stoll(curr_str);
      for (const auto& number : numbers) {
        if (is_plus) result += std::stoll(number);
        else result *= std::stoll(number);
      }
      results += result;
      numbers.clear();
    } else {
      numbers.push_back(curr_str);
    }
  }

  return results;
}

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

  if (argc != 2) {
    results = process(inputs, std::index_sequence<0, 1, 2, 3>{});
  } else {
    results = process(inputs, std::index_sequence<0, 1, 2, 3, 4>{});
  }

  std::cout << "Results: " << results << std::endl;
  return 0;
}
