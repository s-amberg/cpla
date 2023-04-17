#ifndef COMPILE_TIME_MAZE_HPP
#define COMPILE_TIME_MAZE_HPP

#include "Cell.hpp"
#include "Direction.hpp"

#include <algorithm>
#include <array>
#include <functional>
#include <iterator>
#include <ostream>
#include <string>
#include <string_view>
#include <tuple>

template <unsigned NumberOfRows, unsigned NumberOfColumns = NumberOfRows>
struct Maze {
  struct CharRow {
    constexpr CharRow() = default;
    constexpr explicit CharRow(std::string_view line) {
      std::ranges::copy(line, std::begin(characters));
    }

    friend auto operator<<(std::ostream &out, CharRow const &row) -> std::ostream & {
      std::ranges::copy(row.characters, std::ostream_iterator<char>{out});
      return out;
    }

    static constexpr auto ColumnWidth = 4;
    std::array<char, NumberOfColumns * ColumnWidth + 1> characters;
  };

  friend inline auto operator<<(std::ostream &out, Maze const &maze) -> std::ostream & {
    auto charRows = maze.render();
    std::ranges::copy(charRows, std::ostream_iterator<CharRow>{out, "\n"});
    return out;
  }

  [[nodiscard]] constexpr auto At(unsigned row, unsigned column) const -> Cell const & {
    return grid[gridIndex(row, column)];
  }

  [[nodiscard]] constexpr auto At(unsigned row, unsigned column) -> Cell & {
    return grid[gridIndex(row, column)];
  }

  constexpr auto Link(unsigned row, unsigned column, Direction direction) -> void {
    At(row, column).OpenPassage(direction);
    auto [neighborRow, neighborColumn] = neighborCoordinates(row, column, direction);
    At(neighborRow, neighborColumn).OpenPassage(~direction);
  }

  [[nodiscard]] constexpr auto HasNeighbor(unsigned row, unsigned column, Direction direction) const -> bool {
    auto [neighborRow, neighborColumn] = neighborCoordinates(row, column, direction);
    return Exists(neighborRow, neighborColumn);
  }

  [[nodiscard]] constexpr auto Exists(unsigned row, unsigned column) const -> bool {
    return row < NumberOfRows && column < NumberOfColumns;
  }

private:
  using Grid = std::array<Cell, NumberOfRows * NumberOfColumns>;

  Grid grid = generate();

  static constexpr auto generate() -> Grid {
    Grid grid{};
    std::ranges::generate(grid, [index = 0]() mutable {
      auto row = index / NumberOfColumns;
      auto column = index % NumberOfColumns;
      index++;
      return Cell{row, column};
    });
    return grid;
  }

  constexpr auto render() const -> std::array<CharRow, NumberOfRows * 2 + 1> {
    std::array<CharRow, NumberOfRows * 2 + 1> charRows{};
    std::string topLine{"+"};
    for (auto column = 0u; column < NumberOfColumns; column++) {
      topLine += "---+";
    }
    charRows[0] = CharRow{topLine};
    for (auto rowIndex = 0; rowIndex < NumberOfRows; rowIndex++) {
      std::string rowRepresentation{"|"};
      for (auto columnIndex = 0; columnIndex < NumberOfColumns; columnIndex++) {
        rowRepresentation += "   ";
        rowRepresentation += At(rowIndex, columnIndex).HasPassage(Direction::East) ? " " : "|";
      }
      charRows[rowIndex * 2 + 1] = CharRow{rowRepresentation};
      std::string rowDelimiter{"+"};
      for (auto columnIndex = 0u; columnIndex < NumberOfColumns; columnIndex++) {
        char southDelimiter = At(rowIndex, columnIndex).HasPassage(Direction::South) ? ' ' : '-';
        rowDelimiter += std::string(3, southDelimiter);
        rowDelimiter += "+";
      }
      charRows[rowIndex * 2 + 2] = CharRow{rowDelimiter};
    }
    return charRows;
  }

  static constexpr auto gridIndex(unsigned row, unsigned column) -> unsigned {
    return row * NumberOfColumns + column;
  }

  [[nodiscard]] static constexpr auto neighborCoordinates(unsigned row, unsigned column, Direction direction) -> std::tuple<unsigned, unsigned> {
    using ModifiedFunction = std::tuple<unsigned, unsigned> (*)(unsigned, unsigned);
    constexpr std::array<ModifiedFunction, 4> modifier{
        [](unsigned row, unsigned column) {
          return std::tuple{row - 1, column};
        }, // North
        [](unsigned row, unsigned column) {
          return std::tuple{row, column + 1};
        }, // East
        [](unsigned row, unsigned column) {
          return std::tuple{row + 1, column};
        }, // South
        [](unsigned row, unsigned column) {
          return std::tuple{row, column - 1};
        } // West
    };
    return modifier[static_cast<std::size_t>(direction)](row, column);
  }
};

#endif