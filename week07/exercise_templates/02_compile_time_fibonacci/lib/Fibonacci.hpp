#ifndef FIBONACCI_HPP_
#define FIBONACCI_HPP_
#include <array>
#include <ranges>
//TODO: implement a) to c) here

constexpr auto fibo(unsigned i) -> unsigned {
    if (i <= 0) return 0;
    if (i == 1) return 1;
    auto v1 = fibo(i - 1);
    auto v2 = fibo(i - 2);
    return v1 + v2;
}

template<unsigned long long i>
constexpr auto fibo_v = fibo_v<i - 1> + fibo_v<i - 2>;

template<>
constexpr auto fibo_v<0> = 0;

template<>
constexpr auto fibo_v<1> = 1;

constexpr auto operator""_fibo(unsigned long long i) -> unsigned long long{
    if (i <= 0) return 0;
    if (i == 1) return 1;
    return fibo(i - 1) + fibo(i - 2);
}

template<unsigned long long n>
inline auto fiboa_v2() -> std::array<unsigned long long, n>  {
    std::array<unsigned long long, n> arr{};

    for(unsigned long long i = 0; i < n; i++) {
        if (i == 0) arr[0] = 0;
        if (i == 1) arr[1] = 1;
        arr[i] = arr[i-1] + arr[i-2];
    };

    return arr;
}

template <std::size_t n>
inline constexpr auto fiboa() {
  std::array<unsigned long long, n> fibs{};
  for (auto index = 0u; index < n; index++) {
    fibs[index] = fibo(index);
  }
  return fibs;
}

#endif /* FIBONACCI_HPP_ */
