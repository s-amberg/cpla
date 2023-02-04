#include <boost/operators.hpp>
#include <cstddef>
#include <iostream>
#include <iterator>


struct MyIntOutIter {
  using iterator_category = std::output_iterator_tag;
  using value_type = int;
  using difference_type = std::ptrdiff_t;
  using pointer = int*;
  using reference = int&;

  auto operator++() -> MyIntOutIter& { return *this; }
  auto operator++(int) -> MyIntOutIter { return *this; }
  auto operator*() const -> MyIntOutIter const& { return *this; }
  void operator=(value_type val) const { std::cout << "value = " << val << '\n'; }
};

struct MyIntOutIterBoost : boost::output_iterator_helper<MyIntOutIterBoost> {
  void operator=(int val) const { std::cout << "value = " << val << '\n'; }
};

auto main(int argc, char** argv) -> int {
  MyIntOutIter intOutIter{};
  *intOutIter++ = 5;

  MyIntOutIterBoost intOutIterBoost{};
  *intOutIterBoost++ = 5;
}
