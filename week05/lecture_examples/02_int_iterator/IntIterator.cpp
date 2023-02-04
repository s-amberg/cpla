#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>


struct IntIterator {
  using iterator_category = std::input_iterator_tag;
  using value_type = int;
  using difference_type = std::ptrdiff_t;
  using pointer = int*;
  using reference = int&;

  explicit IntIterator(int const start = 0) : value{start} {}

  auto operator==(IntIterator const& r) const -> bool = default;

  auto operator*() const -> value_type { return value; }

  auto operator++() -> IntIterator& {
    ++value;
    return *this;
  }

  auto operator++(int) -> IntIterator {
    auto old = *this;
    ++(*this);
    return old;
  }

 private:
  value_type value;
};

auto main() -> int {
  copy(IntIterator{1}, IntIterator{11},
       std::ostream_iterator<int>{std::cout, ", "});
}
