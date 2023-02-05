#include <array>
#include <iostream>

template <typename Container>
auto extractMiddleElement(Container& container) -> decltype(auto) {
  typename Container::value_type nthElement{};
  std::swap(container.at(container.size() / 2), nthElement);
  return nthElement;
}

auto main(int argc, char** argv) -> int {
  std::array<int, 3> values{1, 2, 3};
  std::cout << "Middle Element: " << extractMiddleElement(values) << '\n';
}
