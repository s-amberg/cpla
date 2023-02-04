#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <sstream>

struct IntInputter {
  using iterator_category = std::input_iterator_tag;
  using value_type = int;
  using difference_type = std::ptrdiff_t;
  using pointer = int*;
  using reference = int&;

  IntInputter();
  explicit IntInputter(std::istream& in) : input{in} {}
  auto operator*() -> value_type;
  auto operator++() -> IntInputter& { return *this; }
  auto operator++(int) -> IntInputter {
    IntInputter old{*this};
    ++(*this);
    return old;
  }
  auto operator==(IntInputter const& other) const -> bool;

 private:
  std::istream& input;
};

namespace {
// a global helper needed...
std::istringstream empty{};
}  // namespace

IntInputter::IntInputter() : input{empty} {
  // guarantee the empty stream is not good()
  input.clear(std::ios_base::eofbit);
}

auto IntInputter::operator*() -> IntInputter::value_type {
  value_type value{};
  input >> value;
  return value;
}

auto IntInputter::operator==(const IntInputter& other) const -> bool {
  return !input.good() && !other.input.good();
}

auto main(int argc, char** argv) -> int {
  std::istringstream input{"1 2 3"};
  std::copy(IntInputter{input}, IntInputter{},
            std::ostream_iterator<int>{std::cout, "\n"});
}
