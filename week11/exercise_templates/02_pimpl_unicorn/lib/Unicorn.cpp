#include "Unicorn.hpp"

#include <ostream>
#include <string>
#include <utility>

Unicorn::Unicorn(std::string name, std::string color) :
  m_name{std::move(name)}, m_color{std::move(color)} {}

void Unicorn::glitter(std::ostream & out) const {
  out << m_name << " glitters beautifully\n";
}

void Unicorn::fly(std::ostream & out) const {
  out << m_name << " flies at " << calculateAltitude() << "m\n";
}

auto Unicorn::operator==(Unicorn const & other) const -> bool {
	return m_name == other.m_name && m_color == other.m_color;
}
auto Unicorn::operator!=(Unicorn const & other) const -> bool {
	return !(*this == other);
}

auto Unicorn::calculateAltitude() const -> int {
  return 8 * m_color.size();
}
