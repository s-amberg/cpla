#ifndef CELL_HPP
#define CELL_HPP

#include "Direction.hpp"

#include <array>
#include <cstddef>

struct Cell {
  constexpr Cell(unsigned row, unsigned column) : row{row}, column{column} {}

  constexpr Cell() = default;

  constexpr auto Row() -> unsigned const {
    return row;
  }

  constexpr auto Column() -> unsigned const {
    return column;
  }

  constexpr auto OpenPassage(Direction direction) -> void {
    passages[static_cast<std::size_t>(direction)] = true;
  }

  [[nodiscard]] constexpr auto HasPassage(Direction direction) const -> bool {
    return passages[static_cast<std::size_t>(direction)];
  }

private:
  unsigned row;
  unsigned column;
  std::array<bool, NumberOfDirections> passages{}; // TODO: Use std::bitset with C++23
};

#endif