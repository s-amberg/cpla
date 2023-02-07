#include <iostream>
#include <string>

template <typename First, typename... Types>
auto printAll(First const& first, Types const&... rest) -> void {
  std::cout << first;
  if constexpr (sizeof...(Types)) {
    std::cout << ", ";
    printAll(rest...);
  }
}

auto main(int argc, char** argv) -> int {
  int i{42};
  double d{1.25};
  std::string book{"Lucid C++"};
  printAll(i, d, book);
}
