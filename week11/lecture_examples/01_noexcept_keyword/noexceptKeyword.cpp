#include <iostream>

auto default_specification() -> void {}

auto function() noexcept -> void {}

////Cannot overload on noexcept
// auto function() {
// }

template <bool NoException>
auto function(int) noexcept(NoException) -> void {}

auto main() -> int {
  std::cout << std::boolalpha;
  std::cout << "is default_specification() noexcept? " << noexcept(default_specification()) << '\n';
  std::cout << "is function() noexcept? " << noexcept(function()) << '\n';
  std::cout << "is function<true>(int) noexcept? " << noexcept(function<true>(1)) << '\n';
  std::cout << "is function<false>() noexcept? " << noexcept(function<false>(1)) << '\n';
}
