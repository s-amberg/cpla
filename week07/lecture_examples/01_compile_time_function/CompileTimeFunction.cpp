#include <iostream>

constexpr auto factorial(unsigned n) -> unsigned {
  auto result = 1u;
  for (auto i = 2u; i <= n; i++) {
    result *= i;
  }
  return result;
}

constexpr auto foo(int n) -> void {
  if (n < 1) {
    new int{};
  }
}

constexpr auto factorialOf5 = factorial(5);

auto main() -> int {
  static_assert(factorialOf5 == 120);
  std::cout << factorial(5);
}
