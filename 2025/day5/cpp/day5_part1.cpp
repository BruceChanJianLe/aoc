#include <iostream>
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

  std::vector<long> lows;
  std::vector<long> highs;
  std::vector<long> ids;
  for (const auto& input : inputs) {
    std::string token{input.begin(), input.end()};
    auto pos{token.find('-')};
    if (pos == std::string::npos) {
      if (!input.empty()) {
        ids.push_back(std::stol(input));
      }
    }
    else {
      lows.push_back(std::stol(token.substr(0, pos)));
      highs.push_back(std::stol(token.substr(pos + 1)));
    }
  }

  int count{0};
  for (const auto& id : ids) {
    for (int i = 0; i < lows.size(); ++i) {
      if (id >= lows[i]) {
        if (id <= highs[i]) {
          count++;
          break;
        }
      }
    }
  }

  std::cout << "count: " << count << std::endl;

  return 0;
}
