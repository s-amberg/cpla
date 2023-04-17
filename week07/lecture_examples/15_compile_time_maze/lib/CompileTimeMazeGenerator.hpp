#ifndef COMPILE_TIME_MAZE_GENERATOR_HPP
#define COMPILE_TIME_MAZE_GENERATOR_HPP

#include "CompileTimeMaze.hpp"
#include "CompileTimeRandom.hpp"

#include <vector>

constexpr auto ParseTime(char const *time) -> unsigned {
  auto digitValue = [](char c) { return c - '0'; };
  unsigned value{};
  value += digitValue(time[0]) * 10;
  value += digitValue(time[1]);
  value *= 60;
  value += digitValue(time[3]) * 10;
  value += digitValue(time[4]);
  value *= 60;
  value += digitValue(time[6]) * 10;
  value += digitValue(time[7]);
  return value;
}

template <unsigned Rows, unsigned Columns = Rows>
constexpr auto Sidewinder() -> Maze<Rows, Columns> {
  Rng<> generator{ParseTime(__TIME__)};

  Maze<Rows, Columns> maze{};
  for (auto row = 0u; row < Rows; row++) {
    std::vector<Cell> run{};

    for (auto column = 0u; column < Columns; column++) {
      auto &cell = maze.At(row, column);
      run.push_back(cell);

      bool atNorthernBoundary = !maze.HasNeighbor(row, column, Direction::North);
      bool atEasternBoundary = !maze.HasNeighbor(row, column, Direction::East);
      bool shouldCloseOut = atEasternBoundary || (!atNorthernBoundary && generator.nextBool());

      if (shouldCloseOut) {
        auto index = generator.next() % run.size();
        auto member = run[index];
        if (!atNorthernBoundary) {
          maze.Link(member.Row(), member.Column(), Direction::North);
        }
        run.clear();
      } else {
        maze.Link(row, column, Direction::East);
      }
    }
  }
  return maze;
}

#endif