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
  long counts{0};
  for (const auto& input : inputs) {
    std::string token{input.begin(), input.end()};
    auto pos{token.find('-')};
    if (pos == std::string::npos) break;

    std::vector<long> check_lows{std::stol(token.substr(0, pos))};
    std::vector<long> check_highs{std::stol(token.substr(pos + 1))};
    for (int i = 0; i < lows.size(); ++i) {
      for (int j = 0; j < check_lows.size(); ++j) {
        if (check_lows[j] < lows[i] && check_highs[j] >= lows[i] && check_highs[j] <= highs[i]) {
          check_highs[j] = lows[i] - 1;
        }
        else if (check_lows[j] < lows[i] && check_highs[j] > highs[i]) {
          check_lows.push_back(highs[i] + 1);
          check_highs.push_back(check_highs[j]);
          check_highs[j] = lows[i] - 1;
        }
        else if (check_lows[j] >= lows[i] && check_highs[j] <= highs[i]) {
          // discard this range
          check_lows.erase(check_lows.begin() + j);
          check_highs.erase(check_highs.begin() + j);
        }
        else if (check_lows[j] >= lows[i] && check_lows[j] <= highs[i] && check_highs[j] > highs[i]) {
          check_lows[j] = highs[i] + 1;
        }
      }
    }

    lows.insert(lows.end(), check_lows.begin(), check_lows.end());
    highs.insert(highs.end(), check_highs.begin(), check_highs.end());
  }

  long count{0};
  for (int i = 0; i < lows.size(); ++i) {
    count += highs[i] - lows[i] + 1;
  }

  std::cout << "count: " << count << std::endl;

  return 0;
}
