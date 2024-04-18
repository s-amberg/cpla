#include "BoundedBuffer.hpp"

#include <boost/type_index.hpp>
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>

TEST_CASE("BoundedBuffer<int, 1000> const is empty()", "[Default Behavior Suite]") {
  BoundedBuffer<int, 1000> const buffer{};
  REQUIRE(buffer.empty());
}

TEST_CASE("BoundedBuffer<int, 0> is empty", "[Default Behavior Suite]") {
  BoundedBuffer<int, 0> const buffer{};
  REQUIRE(buffer.empty());
}

TEST_CASE("BoundedBuffer<int, 1000> const is not full", "[Default Behavior Suite]") {
  BoundedBuffer<int, 1000> const buffer{};
  REQUIRE_FALSE(buffer.full());
}

TEST_CASE("BoundedBuffer<int, 0> is full", "[Default Behavior Suite]") {
  BoundedBuffer<int, 0> const buffer{};
  REQUIRE(buffer.full());
}

TEST_CASE("BoundedBuffer<int, 1000> const has size 0", "[Default Behavior Suite]") {
  BoundedBuffer<int, 1000> const buffer{};
  REQUIRE(buffer.size() == 0);
}

TEST_CASE("BoundedBuffer<int, 0> const has size 0", "[Default Behavior Suite]") {
  BoundedBuffer<int, 0> const buffer{};
  REQUIRE(buffer.size() == 0);
}

TEST_CASE("Empty BoundedBuffer throws on front()", "[Default Behavior Suite]") {
  BoundedBuffer<int, 23> buffer{};
  REQUIRE_THROWS_AS(buffer.front(), std::logic_error);
}

TEST_CASE("Empty BoundedBuffer const throws on front()", "[Default Behavior Suite]") {
  BoundedBuffer<int, 23> const buffer{};
  REQUIRE_THROWS_AS(buffer.front(), std::logic_error);
}

TEST_CASE("Empty BoundedBuffer throws on back()", "[Default Behavior Suite]") {
  BoundedBuffer<int, 23> buffer{};
  REQUIRE_THROWS_AS(buffer.back(), std::logic_error);
}

TEST_CASE("Empty BoundedBuffer const throws on back()", "[Default Behavior Suite]") {
  BoundedBuffer<int, 23> const buffer{};
  REQUIRE_THROWS_AS(buffer.back(), std::logic_error);
}

TEST_CASE("Empty BoundedBuffer throws on pop()", "[Default Behavior Suite]") {
  BoundedBuffer<int, 23> buffer{};
  REQUIRE_THROWS_AS(buffer.pop(), std::logic_error);
}

TEST_CASE("Full BoundedBuffer throws on push(const_lvalue)", "[Default Behavior Suite]") {
  BoundedBuffer<int, 0> buffer{};
  int const lvalue{23};
  REQUIRE_THROWS_AS(buffer.push(lvalue), std::logic_error);
}

TEST_CASE("Full BoundedBuffer throws on push(rvalue)", "[Default Behavior Suite]") {
  BoundedBuffer<int, 0> buffer{};
  REQUIRE_THROWS_AS(buffer.push(23), std::logic_error);
}
