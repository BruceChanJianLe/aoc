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
    counter += move / 100;
    move %= 100;

    if (input.front() == 'L') {
      // if current idx is not zero, moving leftwards by more than current idx will result in passing zero
      if (move >= curr_idx && curr_idx != 0) ++counter;
      move = 100 - move;
    } else {
      // moving rightwards more than or equal the difference between 100 and current idx will result in passing or landing on zero
      if (move >= 100 - curr_idx) ++counter;
    }

    curr_idx = (curr_idx + move) % 100;
  }

  std::cout << "counter: " << counter << std::endl;

  return 0;
}
