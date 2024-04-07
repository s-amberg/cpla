
#include "Fibonacci.hpp"
#include "catch2/catch_message.hpp"

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include <array>
#include <cstddef>

//--------- 1a) ---------
static_assert(0 == fibo(0), "fibo(0)");
static_assert(1 == fibo(1), "fibo(1)");
static_assert(1 == fibo(2), "fibo(2)");
static_assert(2 == fibo(3), "fibo(3)");
static_assert(3 == fibo(4), "fibo(4)");
static_assert(5 == fibo(5), "fibo(5)");
// static_assert(1'836'311'903 == fibo(46), "fibo(46)");

//--------- 1b) ---------
static_assert(0 == fibo_v<0>, "fibo_v<0>");
static_assert(1 == fibo_v<1>, "fibo_v<1>");
static_assert(1 == fibo_v<2>, "fibo_v<2>");
static_assert(2 == fibo_v<3>, "fibo_v<3>");
static_assert(3 == fibo_v<4>, "fibo_v<4>");
static_assert(5 == fibo_v<5>, "fibo_v<5>");
// static_assert(1'836'311'903 == fibo_v<46>, "fibo_v<46>");

//--------- 1c) ---------
static_assert(0 == 0_fibo, "0_fibo");
static_assert(1 == 1_fibo, "1_fibo");
static_assert(1 == 2_fibo, "2_fibo");
static_assert(2 == 3_fibo, "3_fibo");
static_assert(3 == 4_fibo, "4_fibo");
static_assert(5 == 5_fibo, "5_fibo");
// static_assert(1'836'311'903 == 46_fibo, "46_fibo");

//--------- 1d) ---------
TEST_CASE("Fibonacci calculation", "[Fibonacci Suite]") {
  auto [input, expected] = GENERATE(table<unsigned long long, unsigned long long>({
    {0, 0}, 
    {1, 1}, 
    {2, 1}, 
    {3, 2}, 
    {4, 3}, 
    {5, 5}, 
    {46, 1836311903}
    }));
  CAPTURE(input, expected);
  REQUIRE(fibo(input) == expected);
}

//--------- 2a) ---------
constexpr std::array<unsigned long long, 6> expected{0, 1, 1, 2, 3, 5};

template <typename T, std::size_t N>
constexpr auto arrayEquals(std::array<T, N> const &lhs, std::array<T, N> const &rhs) -> bool {
  for (auto index = 0u; index < N; index++) {
    if (lhs[index] != rhs[index]) {
      return false;
    }
  }
  return true;
}

// template <typename T, unsigned long long N, unsigned long long...I>
// constexpr bool allEqualFold(std::array<T, N> const & lhs, std::array<T, N>
// const & rhs, std::index_sequence<I...>) { 	return ((lhs[I] == rhs[I]) && ...);
// }
//
// template <typename T, unsigned long long N>
// constexpr bool arrayEquals(std::array<T, N> const & lhs, std::array<T, N>
// const & rhs) { 	return allEqualFold(lhs, rhs, std::make_index_sequence<N>());
// }

static_assert(arrayEquals(expected, fiboa<6>()));

//--------- 2b) ---------
static_assert(arrayEquals(expected, fiboa_v<6>));

//--------- 2c) ---------
static_assert(arrayEquals(expected, 6_fiboa));
