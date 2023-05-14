#include "Wizard.hpp"

#include <iostream>

auto main() -> int {
  Wizard w{"Gandalf"};

  std::cout << w.doMagic("Earthquake");
}
