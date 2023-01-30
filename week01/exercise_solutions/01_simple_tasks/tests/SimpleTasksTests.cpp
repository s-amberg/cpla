#include "Increment.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

#include <iterator>
#include <limits>
#include <stdexcept>
#include <vector>

TEST(testIncrementReturnsOneForZero) {
  ASSERT_EQUAL(1, incrementByValue(0));
}

TEST(testIncrementReturns42For41) {
  ASSERT_EQUAL(42, incrementByValue(41));
}

TEST(testIncrementSideEffectOneForZero) {
  int i{0};
  increment(i);
  ASSERT_EQUAL(1, i);
}

TEST(testIncrementSideEffect42For41) {
  int i{41};
  increment(i);
  ASSERT_EQUAL(42, i);
}

TEST(testMaxIntCannotBeIncremented) {
  int i{std::numeric_limits<int>::max()};
  ASSERT_THROWS(increment(i), std::overflow_error);
}

TEST(testIncrementDoesNotChangeParameterOnError) {
  int i{std::numeric_limits<int>::max()};
  try {
    increment(i);
  } catch (std::overflow_error const&) {
    ASSERT_EQUAL(std::numeric_limits<int>::max(), i);
  }
}

TEST(testIncrementDoubleZeroToOne) {
  double i{0.0};
  increment(i);
  ASSERT_EQUAL(1.0, i);
}

TEST(testIncrementUnsignedLongLongOverflow) {
  unsigned long long max = std::numeric_limits<unsigned long long>::max();
  unsigned long long const expected =
      std::numeric_limits<unsigned long long>::min();
  increment(max);
  ASSERT_EQUAL(expected, max);
}

TEST(testIncrementUnsignedOverflow) {
  unsigned max = std::numeric_limits<unsigned>::max();
  unsigned const expected = std::numeric_limits<unsigned>::min();
  increment(max);
  ASSERT_EQUAL(expected, max);
}

TEST(testIncrementUnsignedCharOverflow) {
  unsigned char max = std::numeric_limits<unsigned char>::max();
  unsigned char const expected = std::numeric_limits<unsigned char>::min();
  increment(max);
  ASSERT_EQUAL(expected, max);
}

TEST(testIncrementSignedCharOverflowThrows) {
  char max = std::numeric_limits<char>::max();
  ASSERT_THROWS(increment(max), std::overflow_error);
}

TEST(testIncrementIterator) {
  std::vector<int> v{1};
  auto it = std::begin(v);
  increment(it, std::end(v));
  ASSERT_EQUAL(std::end(v), it);
}

TEST(testIncrementEndIteratorThrows) {
  std::vector<int> v{1};
  auto it = std::end(v);
  ASSERT_THROWS(increment(it, std::end(v)), std::overflow_error);
}

TEST(testIncrementWithCustomLimitThrows) {
  double d{9.5};
  ASSERT_THROWS(increment(d, 9.0), std::overflow_error);
}

auto main(int argc, char const* argv[]) -> int {
  auto suite = cute::suite{"Simple Tasks Suite",
                           {
                               testIncrementReturnsOneForZero,
                               testIncrementReturns42For41,
                               testIncrementSideEffectOneForZero,
                               testIncrementSideEffect42For41,
                               testMaxIntCannotBeIncremented,
                               testIncrementDoesNotChangeParameterOnError,
                               testIncrementDoubleZeroToOne,
                               testIncrementIterator,
                               testIncrementEndIteratorThrows,
                               testIncrementWithCustomLimitThrows,
                               testIncrementUnsignedOverflow,
                               testIncrementUnsignedLongLongOverflow,
                               testIncrementUnsignedCharOverflow,
                               testIncrementSignedCharOverflowThrows,
                           }};

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}