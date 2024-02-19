#include "BoundedBuffer.hpp"

#include <boost/type_index.hpp>
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>


TEST_CASE("BoundedBuffer<int> const with capacity 0 throws", "[Default Behavior Suite]") {
  // REQUIRE_THROWS_AS(BoundedBuffer<int>{0}, std::invalid_argument);
}

TEST_CASE("BoundedBuffer<int> const with capacity 1000 is empty()", "[Default Behavior Suite]") {
  // BoundedBuffer<int> const buffer{1000};
  // REQUIRE(buffer.empty());
}

TEST_CASE("BoundedBuffer<int> const with capacity 1000 is not full", "[Default Behavior Suite]") {
  // BoundedBuffer<int> const buffer{1000};
  // REQUIRE_FALSE(buffer.full());
}

TEST_CASE("BoundedBuffer<int> const with capacity 1000 has size 0", "[Default Behavior Suite]") {
  // BoundedBuffer<int> const buffer{1000};
  // REQUIRE(buffer.size() == 0);
}

TEST_CASE("Empty BoundedBuffer throws on front()", "[Default Behavior Suite]") {
  // BoundedBuffer<int> buffer{23};
  // REQUIRE_THROWS_AS(buffer.front(), std::logic_error);
}

TEST_CASE("Empty BoundedBuffer const throws on front()", "[Default Behavior Suite]") {
  // BoundedBuffer<int> const buffer{23};
  // REQUIRE_THROWS_AS(buffer.front(), std::logic_error);
}

TEST_CASE("Empty BoundedBuffer throws on back()", "[Default Behavior Suite]") {
  // BoundedBuffer<int> buffer{23};
  // REQUIRE_THROWS_AS(buffer.back(), std::logic_error);
}

TEST_CASE("Empty BoundedBuffer const throws on back()", "[Default Behavior Suite]") {
  // BoundedBuffer<int> const buffer{23};
  // REQUIRE_THROWS_AS(buffer.back(), std::logic_error);
}

TEST_CASE("Empty BoundedBuffer throws on pop()", "[Default Behavior Suite]") {
  // BoundedBuffer<int> buffer{23};
  // REQUIRE_THROWS_AS(buffer.pop(), std::logic_error);
}

TEST_CASE("Full BoundedBuffer throws on push(const_lvalue)", "[Default Behavior Suite]") {
  // BoundedBuffer<int> buffer{1};
  // int const lvalue{23};
  // buffer.push(lvalue);
  // REQUIRE_THROWS_AS(buffer.push(lvalue), std::logic_error);
}

TEST_CASE("Full BoundedBuffer throws on push(rvalue)", "[Default Behavior Suite]") {
  // BoundedBuffer<int> buffer{1};
  // int const lvalue{23};
  // buffer.push(lvalue);
  // REQUIRE_THROWS_AS(buffer.push(23), std::logic_error);
}
