#ifndef UNICORN
#define UNICORN

#include "PimplPtr.hpp"

#include <string>

struct Unicorn {
  Unicorn(std::string name, std::string color);

  auto glitter(std::ostream &out) const -> void;
 
  auto fly(std::ostream &out) const -> void;

  auto operator==(Unicorn const &other) const -> bool;
  auto operator!=(Unicorn const &other) const -> bool;

private:
  PimplPtr<class UnicornImpl> pimpl;
};

#endif
