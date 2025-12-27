#include "input_reader.hpp"

int main (int argc, char *argv[])
{
  static const char* default_input = "test";

  std::string_view input;
  if (argc != 2) {
    input = default_input;
  } else if (argc == 2){
    input = argv[1];
  }

  auto inputs = aoc::InputReader::get_input<std::string>(input);

  // Still thinking...

  return 0;
}
