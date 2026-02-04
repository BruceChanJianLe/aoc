#include <iostream>
#include <ranges>
#include <vector>
#include <string_view>
#include <algorithm>

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

  std::vector<std::string> lines;
  std::vector<char> operators;
  std::vector<int> num_chars;
  int length{0};
  for (const auto& input : inputs) {
    if (input.front() == '+' || input.front() == '*') {
      auto current = input.find_first_not_of(' ');
      while (current != std::string::npos) {
        auto next = input.find_first_not_of(' ', current + 1);
        if (next != std::string::npos) {
          num_chars.push_back(next - current - 1);
          length += next - current;
        } else {
          num_chars.emplace_back();
        }
        operators.emplace_back(input[current]);
        current = next;
      }
    }
    else {
      lines.emplace_back(input.begin(), input.end());
    }
  }
  num_chars.back() = lines.front().size() - length;

  std::vector<std::vector<std::string>> numbers;
  for (const auto& line : lines) {
    numbers.emplace_back();
    int line_idx = 0;
    for (int i = 0; i < num_chars.size(); ++i) {
      numbers.back().emplace_back(line, line_idx, num_chars[i]);
      line_idx += num_chars[i] + 1;
    }
  }

  long answer;
  long grand_total{0l};
  for (int c = 0; c < numbers.front().size(); ++c) {
    if (operators[c] == '*') {
      answer = 1l;
    }
    else {
      answer = 0l;
    }
    for (int i = 0; i < num_chars[c]; ++i) {
      std::string number{};
      for (int r = 0; r < numbers.size(); ++r) {
        if (numbers[r][c][i] != ' ') {
          number.push_back(numbers[r][c][i]);
        }
      }
      if (operators[c] == '*') {
        answer *= std::stol(number);
      }
      else{
        answer += std::stol(number);
      }
    }
    grand_total += answer;
  }

  std::cout << "grand total: " << grand_total << std::endl;
  return 0;
}
