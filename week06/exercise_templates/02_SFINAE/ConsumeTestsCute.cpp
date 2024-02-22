#include "Consume.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

TEST(testConsumeWithIntArgumentsReturnInteger) {
  // ASSERT_EQUAL(Result::Integer, consume(1));
  // ASSERT_EQUAL(Result::Integer, consume(1l));
  // ASSERT_EQUAL(Result::Integer, consume(1ll));
  // ASSERT_EQUAL(Result::Integer, consume(1u));
  // ASSERT_EQUAL(Result::Integer, consume(1ul));
  // ASSERT_EQUAL(Result::Integer, consume(1ull));
}

TEST(testConsumeWithFloatArgumentsReturnFloat) {
  // ASSERT_EQUAL(Result::Float, consume(1.0f));
  // ASSERT_EQUAL(Result::Float, consume(1.0));
  // ASSERT_EQUAL(Result::Float, consume(1.0l));
}

TEST(testConsumeWithOtherArgumentsReturnOther) {
  using namespace std::string_literals;
  ASSERT_EQUAL(Result::Other, consume("other"s));
  ASSERT_EQUAL(Result::Other, consume(std::vector<int>{1, 2, 3}));
  ASSERT_EQUAL(Result::Other, consume(std::istringstream{"other"s}));
}

auto main(int argc, char const* argv[]) -> int {
  auto suite = cute::suite{"Consume Tests",
                           {
                               testConsumeWithIntArgumentsReturnInteger,
                               testConsumeWithOtherArgumentsReturnOther,
                               testConsumeWithFloatArgumentsReturnFloat,
                           }};

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}