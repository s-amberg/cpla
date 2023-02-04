#include "LineIterator.hpp"

#include <iostream>
#include <iterator>

auto main() -> int {
  LineIterator input_iter{std::cin};
  LineIterator eof{};
  std::cout << std::distance(input_iter, eof);
}
