#include <iostream>
#include <ostream>
#include <thread>

struct Functor {
  auto operator()() const -> void {
    std::cout << "Functor" << std::endl;
  }
};

auto function() -> void {
  std::cout << "Function" << std::endl;
}

auto main() -> int {
  std::thread functionThread{function};
  std::thread functorThread{Functor{}};

  functorThread.join();
  functionThread.join();
}
