#include <cstddef>

#include <iostream>
#include <thread>


std::size_t fibonacci(std::size_t n) {
	if (n < 2) {
		return n;
	}
	return fibonacci(n - 1) + fibonacci(n - 2);
}

void printFib(std::size_t n) {
	auto fib = fibonacci(n);
  std::cout << "fib(" << n << ") is " << fib << '\n';

}

int main() {
  std::thread function { printFib, 46 };
  std::cout << "waiting..." << std::endl;
  function.join();
}
