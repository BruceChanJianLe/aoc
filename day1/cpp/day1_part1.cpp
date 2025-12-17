#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  std::ifstream file("input.txt");
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
    move %= 100;
    if (input.front() == 'L') {
      move = 100 - move;
    }
    curr_idx = (curr_idx + move) % 100;
    if (0 == curr_idx)
      ++counter;
  }

  std::cout << "counter: " << counter << std::endl;

  return 0;
}
