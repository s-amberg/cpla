#include <iostream>
#include <thread>

auto main() -> int {
  std::thread lambda{[] { std::cout << "Lambda" << std::endl; }};
  std::cout << "Main" << std::endl;
}
