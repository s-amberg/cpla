#include "Vector.hpp"

#include "Constants.hpp"

#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <stdexcept>


TEST_CASE("Create vector with single element", "[Vector Literal Suite]") {
  // constexpr Vector<double, 1> v{1.0};
  // static_assert(v[0] == 1.0);
  // REQUIRE(v[0] == 1.0);
}

TEST_CASE("Create vector with two elements", "[Vector Literal Suite]") {
  // constexpr Vector<double, 2> v{1.0, 2.0};
  // static_assert(v[0] == 1.0);
  // static_assert(v[1] == 2.0);
  // REQUIRE(v[0] == 1.0);
  // REQUIRE(v[1] == 2.0);
}

TEST_CASE("Create vector without elements", "[Vector Literal Suite]") {
  // constexpr Vector<double, 0> v{};
  // REQUIRE(true);
}

TEST_CASE("Access out of bounds throws", "[Vector Literal Suite]") {
  // constexpr Vector<double, 1> v{1.0};
  // // static_assert(v[1] == 0.0);
  // REQUIRE_THROWS_AS(v[1], std::out_of_range);
}

TEST_CASE("Deduce template arguments", "[Vector Literal Suite]") {
  // constexpr Vector v{1.0, 2.0};
  // static_assert(v[0] == 1.0);
  // static_assert(v[1] == 2.0);
  // REQUIRE(v[0] == 1.0);
  // REQUIRE(v[1] == 2.0);
}

// constexpr auto create() {
//   Vector v{1.0, 2.0};
//   v[0] = 3.0;
//   return v;
// }

TEST_CASE("Allow modification of non-const element", "[Vector Literal Suite]") {
  // constexpr auto v = create();
  // static_assert(v[0] == 3.0);
  // static_assert(v[1] == 2.0);
  // REQUIRE(v[0] == 3.0);
  // REQUIRE(v[1] == 2.0);
}

TEST_CASE("Calculate length of zero vector", "[Vector Literal Suite]") {
  // constexpr Vector v{0.0, 0.0, 0.0, 0.0};
  // constexpr auto length = v.length();
  // static_assert(length == 0.0);
  // REQUIRE(length == 0.0);
}

TEST_CASE("Calculate length", "[Vector Literal Suite]") {
  // constexpr Vector v{1.0, 2.0, 3.0};
  // constexpr auto length = v.length();
  // static_assert(length == sqrt_14);
  // REQUIRE(length == sqrt_14);
}

TEST_CASE("Calculate length of unit vector", "[Vector Literal Suite]") {
  // constexpr Vector v{1.0 / sqrt_14, 2.0 / sqrt_14, 3.0 / sqrt_14};
  // constexpr auto length = v.length();
  // static_assert(length == 1.0);
  // REQUIRE(length == 1.0);
}

TEST_CASE("Equality comparison", "[Vector Literal Suite]") {
  // constexpr Vector v{1.0, 2.5, 3.2};
  // static_assert(v == v);
  // REQUIRE(v == v);
}

TEST_CASE("Unequality comparison", "[Vector Literal Suite]") {
  // constexpr Vector lhs{1.0, 2.5, 3.3};
  // constexpr Vector rhs{1.0, 2.5, 3.1};
  // static_assert(lhs != rhs);
  // REQUIRE(lhs != rhs);
}

TEST_CASE("Output operator", "[Vector Literal Suite]") {
  // constexpr Vector v{1.1, 2.5, 3.3};
  // std::ostringstream out{};
  // out << v;
  // REQUIRE(out.str() == "(1.1, 2.5, 3.3)");
}

TEST_CASE("Scalar product", "[Vector Literal Suite]") {
  // constexpr Vector lhs{1.0, 2.0, 3.0, 4.0};
  // constexpr Vector rhs{4.2, 1.1, 0.0, 9.5};
  // constexpr double expected = 44.4;
  // static_assert(lhs.scalarProduct(rhs) == expected);
  // REQUIRE(lhs.scalarProduct(rhs) == expected);
}