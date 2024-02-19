#ifndef FIBONACCIITERATOR_HPP_
#define FIBONACCIITERATOR_HPP_

#include <cstddef>
#include <iterator>

struct FibonacciIterator {
  using iterator_category = std::input_iterator_tag;
  using value_type = int;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;

  explicit FibonacciIterator(int pos = 0) {
    while (pos-- > 0) {
      ++*this;
    }
  }

  auto operator++(int) -> FibonacciIterator {
    auto const old = *this;
    ++*this;
    return old;
  }

  auto operator++() -> FibonacciIterator& {
    auto const newval = f_1 + f_2;
    f_1 = f_2;
    f_2 = newval;
    return *this;
  }

  auto operator==(FibonacciIterator const& rhs) const -> bool = default;

  auto operator*() const -> value_type { return f_1; }

 private:
  value_type f_1{0};
  value_type f_2{1};
};

#endif /* FIBONACCIITERATOR_HPP_ */
