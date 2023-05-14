#ifndef UNICORN
#define UNICORN

#include <memory>
#include <string>

struct Unicorn {
  Unicorn(std::string name, std::string color);
  ~Unicorn();
  Unicorn(Unicorn &&);
  auto operator=(Unicorn &&) -> Unicorn &;

  auto glitter(std::ostream &out) const -> void;
  auto fly(std::ostream &out) const -> void;

  auto operator==(Unicorn const &other) const -> bool;
  auto operator!=(Unicorn const &other) const -> bool;

private:
  std::unique_ptr<class UnicornImpl> pimpl;
};

#endif
