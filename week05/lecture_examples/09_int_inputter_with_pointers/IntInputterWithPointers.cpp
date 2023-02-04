#include <algorithm>
#include <boost/operators.hpp>
#include <iostream>
#include <iterator>
#include <sstream>

struct IntInputterPtrBoost
    : boost::input_iterator_helper<IntInputterPtrBoost, int> {
  IntInputterPtrBoost() = default;
  explicit IntInputterPtrBoost(std::istream& in) : input{&in} {}
  auto operator*() -> IntInputterPtrBoost::value_type;
  auto operator++() -> IntInputterPtrBoost& { return *this; }
  auto operator==(IntInputterPtrBoost const& other) const -> bool;

 private:
  std::istream* input{};
};

auto IntInputterPtrBoost::operator*() -> IntInputterPtrBoost::value_type {
  value_type value{};
  if (input) {
    (*input) >> value;
  }
  return value;
}

auto IntInputterPtrBoost::operator==(IntInputterPtrBoost const& other) const
    -> bool {
  return (!input || !input->good()) && (!other.input || !other.input->good());
}

auto main(int argc, char** argv) -> int {
  std::istringstream input{"1 2 3"};
  std::copy(IntInputterPtrBoost{input}, IntInputterPtrBoost{},
            std::ostream_iterator<int>{std::cout, "\n"});
}
