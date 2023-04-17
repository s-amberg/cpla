#ifndef DIRECTION_HPP
#define DIRECTION_HPP

#include <array>
#include <cstddef>
#include <ostream>
#include <string>

enum class Direction {
  North = 0,
  East = 1,
  South = 2,
  West = 3,
};

static constexpr auto NumberOfDirections = 4;

constexpr auto operator~(Direction direction) -> Direction {
  constexpr std::array opposites{
      Direction::South,
      Direction::West,
      Direction::North,
      Direction::East,
  };
  return opposites[static_cast<std::size_t>(direction)];
}

inline auto operator<<(std::ostream &out, Direction direction) -> std::ostream & {
  using namespace std::string_literals;
  static std::array names{"North"s, "East"s, "South"s, "Wests"s};
  return out << names[static_cast<std::size_t>(direction)];
}

#endif