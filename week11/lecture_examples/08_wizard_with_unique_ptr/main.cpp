#include "Wizard.hpp"
#include <iostream>

auto main(int argc, char **argv) -> int {
  Wizard w{"Gandalf"};

  w.doMagic("Earthquake");
}
