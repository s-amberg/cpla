#include <stdexcept>

constexpr auto throwIfZero(int value) -> void {
  if (value == 0) {
    throw std::logic_error{""};
  }
}

constexpr auto divide(int n, int d) -> int {
  throwIfZero(d);
  return n / d;
}

constexpr auto five = divide(120, 24);
// constexpr auto failure = divide(120, 0);

auto main() -> int {}
