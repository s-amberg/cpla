#ifndef UNICORN
#define UNICORN

#include <memory>
#include <string>

struct Unicorn {
  Unicorn(std::string name, std::string color);
  ~Unicorn();
  Unicorn(Unicorn const &);
  Unicorn(Unicorn &&);
  auto operator=(Unicorn const &) -> Unicorn &;
  auto operator=(Unicorn &&) -> Unicorn &;

  void glitter(std::ostream & out) const;

  void fly(std::ostream & out) const;

  auto operator==(Unicorn const & other) const -> bool;
  auto operator!=(Unicorn const & other) const -> bool;

  private:
    std::unique_ptr<class UnicornImpl> pImpl;
};

#endif
