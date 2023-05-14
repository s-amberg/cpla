#ifndef UNICORN
#define UNICORN

#include <string>

struct Unicorn {
  Unicorn(std::string name, std::string color);

  void glitter(std::ostream & out) const;

  void fly(std::ostream & out) const;

  auto operator==(Unicorn const & other) const -> bool;
  auto operator!=(Unicorn const & other) const -> bool;

  private:
    auto calculateAltitude() const -> int;

    std::string m_name{};
    std::string m_color{};
};

#endif
