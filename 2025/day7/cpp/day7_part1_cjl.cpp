#include <unordered_set>
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

  // split count
  int results{};
  std::unordered_set<int> beams;
  beams.reserve(inputs.front().size());

  for (const auto& input : inputs) {
    if (beams.empty()) {
      beams.insert(input.find_first_of('S'));
    } else {
      std::vector<int> add_beams;
      std::vector<int> remove_beams;
      for (const auto& beam : beams) {
        // Beams hit the splitter
        if (input[beam] == '^') {
          // Left beam (need not do check as input is within bounds)
          add_beams.push_back(beam - 1);
          // Right beam
          add_beams.push_back(beam + 1);
          // Remove current beam
          remove_beams.push_back(beam);
          // Book keeping
          ++results;
        }
      }

      // Add beams
      for (const auto& beam : add_beams) { beams.insert(beam); }

      // Remove beams
      for (const auto& beam : remove_beams) { beams.erase(beam); }
    }
  }

  std::cout << "Results: " << results << std::endl;
  return 0;
}
