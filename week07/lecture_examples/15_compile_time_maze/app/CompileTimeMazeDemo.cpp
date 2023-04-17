
#include "CompileTimeMaze.hpp"
#include "CompileTimeMazeGenerator.hpp"

#include <iostream>

constinit auto maze = Sidewinder<15>();

auto main() -> int {
    std::cout << maze;
}