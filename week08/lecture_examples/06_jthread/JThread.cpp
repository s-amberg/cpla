#include <iostream>
#include <stdexcept>
#include <thread>
#include <utility>

auto main() -> int {
  std::jthread t{[] { std::cout << "Hello Thread" << std::endl; }};
  std::cout << "Hello Main" << std::endl;
}
