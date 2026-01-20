#include <iostream>
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

  std::vector<std::vector<int>> numbers;
  std::vector<char> operators;
  for (const auto& input : inputs) {
    // std::cout << std::string_view(input.begin(), input.end()) << std::endl;
    std::stringstream ss(input);
    std::string word;
    numbers.emplace_back();
    while (ss >> word) {
      if (word == "+" || word == "*") {
        operators.emplace_back(word[0]);
      }
      else {
        numbers.back().emplace_back(std::stoi(word));
      }
    }
  }

  numbers.pop_back();

  long answer;
  long grand_total{0l};
  for (int c = 0; c < numbers.front().size(); ++c) {
    if (operators[c] == '*') {
      answer = 1l;
    }
    else {
      answer = 0l;
    }
    for (int r = 0; r < numbers.size(); ++r) {
      if (operators[c] == '*') {
        answer *= numbers[r][c];
      }
      else{
        answer += numbers[r][c];
      }
    }
    grand_total += answer;
  }

  std::cout << "grand total: " << grand_total << std::endl;
  return 0;
}
