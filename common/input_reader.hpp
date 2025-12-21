#pragma once

#include <string_view>
#include <vector>
#include <fstream>
#include <iostream>

namespace aoc
{
  class InputReader
  {
  public:
    template <typename T>
    static std::vector<T> get_input(std::string_view input) {
      if (input.compare("cjl") == 0) {
        return read_input_file<T>(cjl_input);
      } else if (input.compare("brina") == 0) {
        return read_input_file<T>(bri_input);
      } else if (input.compare("dayna") == 0) {
        return read_input_file<T>(day_input);
      } else {
        return read_input_file<T>(test_input);
      }
    }

  private:
    static constexpr const char* test_input = "test_input.txt";
    static constexpr const char* cjl_input = "cjl_input.txt";
    static constexpr const char* bri_input = "brina_input.txt";
    static constexpr const char* day_input = "dayna_input.txt";

    template <typename T>
    static std::vector<T> read_input_file(std::string_view path) {
      std::ifstream file(path.data());
      std::cout << "Loading " << path << std::endl;
      std::vector<T> inputs;

      for (T line; std::getline(file, line);) {
        inputs.emplace_back(line);
      }

      return inputs;
    }
  };
} // aoc
