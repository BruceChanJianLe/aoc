#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  std::ifstream file("test_input.txt");
  if (!file.is_open()) {
    std::cerr << "Failed to open file\n";
    return 1;
  }

  std::vector<std::string> inputs;
  std::string line;
  while (std::getline(file, line)) {
    inputs.emplace_back(line);
  }
  file.close();

  int curr_idx{50};
  int counter{};

  for (const auto &input : inputs) {
    auto move = std::stoi(input.substr(1));
    // If I pass zero
    // 68 / 100 = 0
    counter += move / 100;
    // move -> 68
    move %= 100;
    if (input.front() == 'L') {
      // me walking backwards
      move = 100 - move;
      // 32 < 50
      if (move < curr_idx) ++counter;
    } else {
      // move >
    }

    // If I pass zero
    counter += (curr_idx + move) / 100;
    curr_idx = (curr_idx + move) % 100;
    // If I land zero :D
    if (0 == curr_idx) ++counter;
  }

  std::cout << "counter: " << counter << std::endl;

  return 0;
}
