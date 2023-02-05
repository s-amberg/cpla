#include <array>
#include <boost/type_index.hpp>
#include <cstddef>
#include <iostream>

template <template <typename, std::size_t> class Container,
          typename Target,
          std::size_t N>
auto extractMiddleElement(Container<Target, N>& container) -> Target {
  Target nthElement{};
  std::swap(container.at(N / 2), nthElement);

  {
    std::cout << "Type of Container => "
              << boost::typeindex::type_id<decltype(container)>().pretty_name()
              << '\n';
    std::cout << "Type of Target\t  => "
              << boost::typeindex::type_id<Target>().pretty_name() << '\n';
    std::cout << "Value of N\t  => " << N << '\n';
  }

  return nthElement;
}

auto main(int argc, char** argv) -> int {
  std::array<int, 3> values{1, 2, 3};
  std::cout << "Middle Element: " << extractMiddleElement(values) << '\n';
}
