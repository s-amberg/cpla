
#include "Fibonacci.hpp"
#include "Measure.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

#include <array>
#include <cstddef>
#include <utility>

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
struct FiboTestData {
  unsigned long long n;
  unsigned long long expected;
  cute::test_failure failure;
} const dataTable[] = {
    {0, 0, DDT()},
    {1, 1, DDT()},
    {2, 1, DDT()},
    {3, 2, DDT()},
    {4, 3, DDT()},
    {5, 5, DDT()},
    {46, 1'836'311'903, DDT()},
};

void testFiboDDT() {
  for (auto const& entry : dataTable) {
    auto duration = measure([&] { fibo(entry.n); });
    std::cout << "calculating n = " << entry.n << " took " << duration.count()
              << " ms\n";
    ASSERT_EQUAL_DDT(entry.expected, fibo(entry.n), entry.failure);
  }
}

//--------- 2a) ---------
constexpr std::array<unsigned long long, 6> expected{0, 1, 1, 2, 3, 5};

template <typename T, std::size_t N>
constexpr auto arrayEquals(std::array<T, N> const& lhs,
                           std::array<T, N> const& rhs) -> bool {
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

auto main(int argc, char const* argv[]) -> int {
  auto suite = cute::suite{"Fibonacci Tests",
                           {
                               testFiboDDT,
                           }};

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}