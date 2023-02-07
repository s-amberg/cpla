#include <cstddef>
#include <cstring>
#include <iostream>


namespace ternary {
namespace _impl {

constexpr auto three_to(std::size_t power) -> unsigned long long {
  return power ? 3ull * three_to(power - 1) : 1ull;
}

constexpr auto is_ternary_digit(char c) -> bool {
  return c == '0' || c == '1' || c == '2';
}

template <char D>
constexpr auto value_of() -> unsigned {
  static_assert(is_ternary_digit(D), "Digits of ternary must be 0, 1 or 2");
  return D - '0';
}

template <char... Digits>
extern unsigned long long ternary_value;

template <char D, char... Digits>
constexpr unsigned long long ternary_value<D, Digits...>{
    value_of<D>() * three_to(sizeof...(Digits)) + ternary_value<Digits...>};

template <>
constexpr unsigned long long ternary_value<>{0};

}  // namespace _impl

template <char... Digits>
constexpr auto operator"" _ternary() -> unsigned long long {
  return _impl::ternary_value<Digits...>;  // C++14
}
}  // namespace ternary

auto main(int argc, char** argv) -> int {
  using namespace ternary;
  std::cout << "11_ternary is " << 11_ternary << '\n';
  std::cout << "02_ternary is " << 02_ternary << '\n';
  std::cout << "120_ternary is " << 120_ternary << '\n';
  //	std::cout << "14_ternary is " << 14_ternary << '\n'; // compile-error
}
