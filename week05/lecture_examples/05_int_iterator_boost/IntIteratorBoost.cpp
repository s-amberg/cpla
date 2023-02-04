#include <algorithm>
#include <boost/operators.hpp>
#include <iostream>
#include <iterator>


struct IntIteratorBoost : boost::input_iterator_helper<IntIteratorBoost, int> {
  explicit IntIteratorBoost(int start = 0) : value{start} {}
  auto operator==(IntIteratorBoost const& r) const -> bool {
    return value == r.value;
  }
  auto operator*() const -> value_type { return value; }
  auto operator++() -> IntIteratorBoost& {
    ++value;
    return *this;
  }

 private:
  int value;
};

auto main() -> int {
  copy(IntIteratorBoost{1}, IntIteratorBoost{11},
       std::ostream_iterator<int>{std::cout, ", "});
}
