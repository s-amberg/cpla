#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

struct SummingIter {
  using iterator_category = std::output_iterator_tag;
  using value_type = int;
  using difference_type = std::ptrdiff_t;
  using pointer = int*;
  using reference = int&;

  void operator++() { ++counter; }
  auto operator*() -> SummingIter& { return *this; }
  void operator=(value_type val) { sum += val; }
  [[nodiscard]] auto average() const -> double { return sum / counter; }
  double sum{};

 private:
  std::size_t counter{};
};

auto main(int argc, char** argv) -> int {
  std::vector<int> v{3, 1, 4, 1, 5, 9, 2};
  auto res = copy(v.begin(), v.end(), SummingIter{});
  std::cout << res.sum << " average: " << res.average();
}
