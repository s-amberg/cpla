#include <iostream>
#include <ostream>
#include <thread>


int main() {
  std::thread greeter {
    [] { std::cout << "Hello, I'm thread!" << std::endl; }
  };
  greeter.join();
}
