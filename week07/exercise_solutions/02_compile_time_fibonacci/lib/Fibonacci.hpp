#ifndef FIBONACCI_HPP_
#define FIBONACCI_HPP_

#include <array>
#include <cctype>
#include <stdexcept>

inline constexpr auto fibo(unsigned n) -> unsigned long long {
  if (n < 2) {
    return n;
  }
  return fibo(n - 1) + fibo(n - 2);
}

// template <unsigned long long n>
// constexpr auto fibo_v = fibo(n);

template <unsigned long long n>
constexpr auto fibo_v = (fibo_v<n - 2>)+(fibo_v<n - 1>);

template <>
constexpr auto fibo_v<0> = 0;

template <>
constexpr auto fibo_v<1> = 1;

inline constexpr auto operator"" _fibo(unsigned long long n)
    -> unsigned long long {
  return fibo(n);
}

template <std::size_t n>
inline constexpr auto fiboa() {
  std::array<unsigned long long, n> fibs{};
  for (auto index = 0u; index < n; index++) {
    fibs[index] = fibo(index);
  }
  return fibs;
}

template <std::size_t n>
constexpr auto fiboa_v = fiboa<n>();

constexpr auto isdigit(char c) -> bool {
  return c >= '0' && c <= '9';
}

namespace {
constexpr inline auto parseDigit(char c) -> unsigned {
  if (!isdigit(c)) {
    throw std::invalid_argument{"c is not a digit"};
  }
  return c - '0';
}

template <char First, char... C>
constexpr inline auto parseSize(unsigned long long previous = 0) {
  constexpr auto digitValue = parseDigit(First);
  auto result = previous + digitValue;
  if constexpr (sizeof...(C)) {
    return parseSize<C...>(result * 10);
  } else {
    return result;
  }
}
}  // namespace

template <char... C>
inline constexpr auto operator"" _fiboa() {
  constexpr auto size = parseSize<C...>();
  return fiboa_v<size>;
}

#endif /* FIBONACCI_HPP_ */
