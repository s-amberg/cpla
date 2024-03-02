#include "Increment.hpp"

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <limits>
#include <stdexcept>
#include <vector>

TEST_CASE("Increment returns one for zero") {
  CHECK(incrementByValue(0) == 1);
}

TEST_CASE("Increment returns 42 for 41") {
  CHECK(incrementByValue(41) == 42);
}

TEST_CASE("Increment side effect one for zero") {
  int i{0};
  increment(i);
  CHECK(i == 1);
}

TEST_CASE("Increment side effect 42 for 41") {
  int i{41};
  increment(i);
  CHECK(i == 42);
}

TEST_CASE("Max int cannot be incremented") {
  int i{std::numeric_limits<int>::max()};
  REQUIRE_THROWS_AS(increment(i), std::overflow_error);
}

TEST_CASE("Increment does not change parameter on error") {
  int i{std::numeric_limits<int>::max()};
  try {
    increment(i);
  } catch (std::overflow_error const&) {
    CHECK(i == std::numeric_limits<int>::max());
  }
}

TEST_CASE("Increment double zero to one") {
  double i{0.0};
  increment(i);
  CHECK(i == 1.0);
}

TEST_CASE("Increment unsigned long long overflow") {
  unsigned long long max = std::numeric_limits<unsigned long long>::max();
  unsigned long long const expected =
      std::numeric_limits<unsigned long long>::min();
  increment(max);
  CHECK(max == expected);
}

TEST_CASE("Increment unsigned overflow") {
  unsigned max = std::numeric_limits<unsigned>::max();
  unsigned const expected = std::numeric_limits<unsigned>::min();
  increment(max);
  CHECK(max == expected);
}

TEST_CASE("Increment unsigned char overflow") {
  unsigned char max = std::numeric_limits<unsigned char>::max();
  unsigned char const expected = std::numeric_limits<unsigned char>::min();
  increment(max);
  CHECK(max == expected);
}

TEST_CASE("Increment signed char overflow throws") {
  char max = std::numeric_limits<char>::max();
  REQUIRE_THROWS_AS(increment(max), std::overflow_error);
}

TEST_CASE("Increment iterator") {
  std::vector<int> v{1};
  auto it = std::begin(v);
  increment(it, std::end(v));
  CHECK(it == std::end(v));
}

TEST_CASE("Increment end iterator throws") {
  std::vector<int> v{1};
  auto it = std::end(v);
  REQUIRE_THROWS_AS(increment(it, std::end(v)), std::overflow_error);
}

TEST_CASE("Increment with custom limit throws") {
  double d{9.5};
  REQUIRE_THROWS_AS(increment(d, 9.0), std::overflow_error);
}