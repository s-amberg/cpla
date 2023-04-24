#include <iostream>
#include <ostream>
#include <thread>

auto main() -> int {
  std::thread greeter {
    [] { std::cout << "Hello, I'm thread!" << std::endl; }
  };
  greeter.join();
}
