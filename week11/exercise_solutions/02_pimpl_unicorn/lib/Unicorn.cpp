#include "Unicorn.hpp"

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

struct UnicornImpl {
  UnicornImpl(std::string name, std::string color) : m_name{std::move(name)}, m_color{std::move(color)} {}

  void glitter(std::ostream &out) const {
    out << m_name << " glitters beautifully\n";
  }

  void fly(std::ostream &out) const {
    out << m_name << " flies at " << calculateAltitude() << "m\n";
  }

  auto operator==(UnicornImpl const &other) const -> bool {
    return m_name == other.m_name && m_color == other.m_color;
  }

private:
  auto calculateAltitude() const -> std::size_t {
    return 8 * m_color.size();
  }

  std::string const m_name{};
  std::string const m_color{};
};

auto Unicorn::operator==(Unicorn const &other) const -> bool {
  return *pimpl == *other.pimpl;
}

auto Unicorn::operator!=(Unicorn const &other) const -> bool {
  return !(*this == other);
}

Unicorn::~Unicorn() = default;

Unicorn::Unicorn(Unicorn &&other) = default;

auto Unicorn::operator=(Unicorn &&) -> Unicorn & = default;

Unicorn::Unicorn(std::string name, std::string color) : pimpl{std::make_unique<UnicornImpl>(std::move(name), std::move(color))} {}

auto Unicorn::glitter(std::ostream &out) const -> void {
  pimpl->glitter(out);
}

auto Unicorn::fly(std::ostream &out) const -> void {
  pimpl->fly(out);
}
