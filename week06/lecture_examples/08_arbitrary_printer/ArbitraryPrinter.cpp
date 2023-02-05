#include <iostream>
#include <string>
#include <utility>

void printAll() {}

template <typename First, typename... Types>
void printAll(First const& first, Types const&... rest) {
  std::cout << first;
  if (sizeof...(Types)) {
    std::cout << ", ";
  }
  printAll(rest...);
}

// template <typename T>
// concept Printable = requires(std::ostream& os, T value) { os << value; };

// void printAll(Printable auto const& first, Printable auto const&... rest) {
//   std::cout << first;
//   if constexpr (sizeof...(rest)) {
//     std::cout << ", ";
//   	printAll(rest...);
//   }
// }

auto main(int argc, char** argv) -> int {
  int i{42};
  double d{1.25};
  std::string book{"Lucid C++"};
  printAll(i, d, book/*, std::cout*/);
}
