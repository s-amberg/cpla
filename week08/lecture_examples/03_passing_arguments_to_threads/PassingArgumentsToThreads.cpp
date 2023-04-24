#include <cstddef>

#include <iostream>
#include <thread>

auto fibonacci(std::size_t n) -> std::size_t {
  if (n < 2) {
    return n;
  }
  return fibonacci(n - 1) + fibonacci(n - 2);
}

auto printFib(std::size_t n) -> void {
  auto fib = fibonacci(n);
  std::cout << "fib(" << n << ") is " << fib << '\n';
}

auto main() -> int {
  std::thread function{printFib, 46};
  std::cout << "waiting..." << std::endl;
  function.join();
}
