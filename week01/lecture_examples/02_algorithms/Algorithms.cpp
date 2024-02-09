#include <algorithm>
#include <chrono>
#include <ios>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>

auto find_with_loop(std::vector<int> const &values, int const v) -> bool {
  auto const end = std::end(values);
  for (auto it = std::begin(values); it != end; ++it) {
    if (*it == v) {
      return true;
    }
  }
  return false;
}

auto find_with_algorithm(std::vector<int> const &values, int const v) -> bool {
  auto const pos = std::find(std::begin(values), std::end(values), v);
  return pos != std::end(values);
}

auto find_with_range_algorithm(std::vector<int> const &values, int const v) -> bool {
  auto const pos = std::ranges::find(values, v);
  return pos != std::end(values);
}

auto execute_measurement(std::vector<int> const &values, std::ostream &out) -> void {
  out << std::boolalpha;

  auto const loop_start = std::chrono::high_resolution_clock::now();
  auto const loop_result = find_with_loop(values, 2);
  auto const loop_end = std::chrono::high_resolution_clock::now();
  auto const loop_duration = std::chrono::duration_cast<std::chrono::milliseconds>(loop_end - loop_start);
  out << "found with a loop: " << loop_result << " in " << loop_duration.count() << "ms" << std::endl;

  auto const algorithm_start = std::chrono::high_resolution_clock::now();
  auto const algorithm_result = find_with_algorithm(values, 2);
  auto const algorithm_end = std::chrono::high_resolution_clock::now();
  auto const algorithm_duration = std::chrono::duration_cast<std::chrono::milliseconds>(algorithm_end - algorithm_start);
  out << "found with an algorithm: " << algorithm_result << " in " << algorithm_duration.count() << "ms" << std::endl;

  auto const range_algorithm_start = std::chrono::high_resolution_clock::now();
  auto const range_algorithm_result = find_with_range_algorithm(values, 2);
  auto const range_algorithm_end = std::chrono::high_resolution_clock::now();
  auto const range_algorithm_duration = std::chrono::duration_cast<std::chrono::milliseconds>(range_algorithm_end - range_algorithm_start);
  out << "found with a range algorithm: " << range_algorithm_result << " in " << range_algorithm_duration.count() << "ms" << std::endl;
}

auto main(int argc, char **argv) -> int {
  std::vector<int> const values(100000000, 1);
  for (auto i = 0; i < 10; i++) {
    execute_measurement(values, std::cout);
  }
}
