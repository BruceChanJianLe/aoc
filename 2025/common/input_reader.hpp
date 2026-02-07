#pragma once

#include <cstddef>
#include <string_view>
#include <system_error>
#include <vector>
#include <fstream>
#include <iostream>
#include <charconv>
#include <algorithm>

namespace aoc
{
  template <typename T>
  bool convert(std::string_view sv, T& value) {
    if (sv.empty()) return false;

    const char* first = sv.data();
    const char* last = sv.data() + sv.size();

    std::from_chars_result result = std::from_chars(first, last, value);

    if (result.ec != std::errc()) return false;
    if (result.ptr != last) return false;

    return true;
  }

  class InputReader
  {
  public:
    template <typename T>
    static std::vector<T> get_input(std::string_view input) {
      return read_input_file<T>(get_filename(input));
    }

    template <typename T, std::size_t N>
    static std::array<T, N> get_input(std::string_view input) {
      return read_input_file<T, N>(get_filename(input));
    }

  private:
    static constexpr const char* test_input = "test_input.txt";
    static constexpr const char* cjl_input = "cjl_input.txt";
    static constexpr const char* bri_input = "brina_input.txt";
    static constexpr const char* day_input = "dayna_input.txt";

    static constexpr const char* get_filename(std::string_view input) {
      if (input.compare("cjl") == 0) {
        return cjl_input;
      } else if (input.compare("brina") == 0) {
        return bri_input;
      } else if (input.compare("dayna") == 0) {
        return day_input;
      } else {
        return test_input;
      }
    }

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

    template <typename T, std::size_t N>
    static std::array<T, N> read_input_file(std::string_view path) {
      std::ifstream file(path.data());
      std::cout << "Loading " << path << std::endl;
      std::array<T, N> store;
      auto it = store.begin();

      for (std::string line; std::getline(file, line);) {
        if constexpr (std::is_same_v<T, std::string>) {
          it = std::copy(line.begin(), line.end(), it);
        } else {
          it = std::transform(line.begin(), line.end(), it,
              [](const auto c){ return static_cast<T>(c); });
        }
      }

      return store;
    }
  };
} // aoc
