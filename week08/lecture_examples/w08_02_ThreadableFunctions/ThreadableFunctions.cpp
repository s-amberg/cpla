#include <iostream>
#include <ostream>
#include <thread>

struct Functor {
  void operator()() const {
    std::cout << "Functor" << std::endl;
  }
};

void function() {
  std::cout << "Function" << std::endl;
}

int main() {
  std::thread functionThread{function};
  std::thread functorThread{Functor{}};

  functorThread.join();
  functionThread.join();
}
