
#include "CompileTimeRandom.hpp"
#include <cstdlib>
#include <iostream>

auto main() -> int {
  Rng<> generator{};
  std::srand(1);
  for (int i = 0; i < 10; i++) {
    std::cout << generator.next() << std::endl;
  }
}