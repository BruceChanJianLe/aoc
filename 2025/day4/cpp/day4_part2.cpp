#include <iostream>
#include <string_view>
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

  std::vector<std::vector<char>> grid;
  for (const auto& input : inputs) {
    grid.emplace_back();
    for (const auto& c : input) {
      grid.back().emplace_back(c);
    }
  }

  int count{0};
  int rolls{0};
  int neighbours{0};
  do
  {
    count += rolls;
    rolls = 0;
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid[i].size(); ++j) {
        if (grid[i][j] == '@') {
          neighbours = 0;
          for (int r = i - 1; r <= i + 1; ++r) {
            for (int c = j - 1; c <= j + 1; ++c) {
              if ((r == i && c == j) || r < 0 || c < 0 || r >= grid.size() || c >= grid[i].size()) continue;
              if (grid[r][c] == '@') {
                if (++neighbours >= 4) break;
              }
            }
            if (neighbours >= 4) break;
          }
          if (neighbours < 4) {
            grid[i][j] = '.';
            rolls++;
          }
        }
      }
    }
  } while (rolls != 0);

  std::cout << "count: " << count << std::endl;

  return 0;
}
