#include "FibonacciIterator.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Default constructed iterator returns zero", "[FibonacciIterator]") {
  FibonacciIterator const fibItr{};
  REQUIRE(*fibItr == 0);
}

TEST_CASE("Fibonacci iterator for first element is one", "[FibonacciIterator]") {
  FibonacciIterator const fibItr{1};
  REQUIRE(*fibItr == 1);
}

TEST_CASE("Fibonacci iterator for second element is one", "[FibonacciIterator]") {
  FibonacciIterator const fibItr{2};
  REQUIRE(*fibItr == 1);
}

TEST_CASE("Fibonacci iterator for third element is two", "[FibonacciIterator]") {
  FibonacciIterator const fibItr{3};
  REQUIRE(*fibItr == 2);
}

TEST_CASE("Fibonacci iterator for fourth element is three", "[FibonacciIterator]") {
  FibonacciIterator const fibItr{4};
  REQUIRE(*fibItr == 3);
}

TEST_CASE("Fibonacci iterator for fifth element is five", "[FibonacciIterator]") {
  FibonacciIterator const fibItr{5};
  REQUIRE(*fibItr == 5);
}

TEST_CASE("Fibonacci iterator for sixth element is eight", "[FibonacciIterator]") {
  FibonacciIterator const fibItr{6};
  REQUIRE(*fibItr == 8);
}

TEST_CASE("Fibonacci iterator for seventh element is thirteen", "[FibonacciIterator]") {
  FibonacciIterator const fibItr{7};
  REQUIRE(*fibItr == 13);
}

TEST_CASE("Fibonacci iterator for eighth element is twentyone", "[FibonacciIterator]") {
  FibonacciIterator const fibItr{8};
  REQUIRE(*fibItr == 21);
}

TEST_CASE("Fibonacci iterator for ninth element is thirtyfour", "[FibonacciIterator]") {
  FibonacciIterator const fibItr{9};
  REQUIRE(*fibItr == 34);
}

TEST_CASE("Fibonacci iterator for tenth element is fiftyfive", "[FibonacciIterator]") {
  FibonacciIterator const fibItr{10};
  REQUIRE(*fibItr == 55);
}

TEST_CASE("Fibonacci iterator equal to itself", "[FibonacciIterator]") {
  FibonacciIterator const fibItr{};
  REQUIRE(fibItr == fibItr);
}

TEST_CASE("Fibonacci iterator equal to other fibonacci iterator with same state", "[FibonacciIterator]") {
  FibonacciIterator const fibItr{10}, otherFibItr{10};
  REQUIRE(fibItr == otherFibItr);
}

TEST_CASE("Fibonacci iterator not equal to other fibonacci iterator with another state", "[FibonacciIterator]") {
  FibonacciIterator const fibItr{5}, otherFibItr{10};
  REQUIRE(fibItr != otherFibItr);
}

TEST_CASE("Prefix incrementing default fibonacci iterator increments this fibonacci iterator", "[FibonacciIterator]") {
  FibonacciIterator const expectedItr{1};
  FibonacciIterator otherFibItr{};
  ++otherFibItr;
  REQUIRE(otherFibItr == expectedItr);
}

TEST_CASE("Prefix incrementing default fibonacci iterator returns changed fibonacci iterator", "[FibonacciIterator]") {
  FibonacciIterator fibItr{};
  FibonacciIterator &changed{++fibItr};
  REQUIRE(&changed == &fibItr);
}

TEST_CASE("Postfix incrementing default fibonacci iterator increments this fibonacci iterator", "[FibonacciIterator]") {
  FibonacciIterator const expectedItr{1};
  FibonacciIterator otherFibItr{};

  otherFibItr++;

  REQUIRE(expectedItr == otherFibItr);
}

TEST_CASE("Postfix incrementing default fibonacci iterator returns previous value fibonacci iterator", "[FibonacciIterator]") {
    FibonacciIterator const expectedItr{};
    FibonacciIterator otherFibItr{};

    FibonacciIterator const unincremented{otherFibItr++};

    REQUIRE(expectedItr == unincremented);
  }

  TEST_CASE("Postfix incrementing default fibonacci iterator returns new fibonacci iterator", "[FibonacciIterator]") {
    FibonacciIterator fibItr{};

    FibonacciIterator const &changed{fibItr++};

    REQUIRE(&changed != &fibItr);
  }
