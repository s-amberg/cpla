#include "CompileTimeComputationFactorial.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

TEST(testFactorialCompiletime) {
  constexpr auto result = fact<5>::value;
  static_assert(result == 2 * 3 * 4 * 5);
  ASSERT_EQUAL(result, 2 * 3 * 4 * 5);
}

auto main(int argc, char const* argv[]) -> int {
  auto suite = cute::suite{"Compile-Time Factorial Tests",
                           {
                               testFactorialCompiletime,
                           }};

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}