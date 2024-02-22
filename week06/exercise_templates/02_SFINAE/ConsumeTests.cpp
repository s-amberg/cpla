#include "Consume.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Consume With Integer Arguments Return Result::Integer", "[SFINAE Suite]") {
  // REQUIRE(consume(1) == Result::Integer);
  // REQUIRE(consume(1l) == Result::Integer);
  // REQUIRE(consume(1ll) == Result::Integer);
  // REQUIRE(consume(1u) == Result::Integer);
  // REQUIRE(consume(1ul) == Result::Integer);
  // REQUIRE(consume(1ull) == Result::Integer);
}

TEST_CASE("Consume With Float Arguments Return Result::Float", "[SFINAE Suite]") {
  // REQUIRE(consume(1.0f) == Result::Float);
  // REQUIRE(consume(1.0) == Result::Float);
  // REQUIRE(consume(1.0l) == Result::Float);
}

TEST_CASE("Consume With Float Arguments Return Result::Other", "[SFINAE Suite]") {
  using namespace std::string_literals;
  REQUIRE(consume("other"s) == Result::Other);
  REQUIRE(consume(std::vector<int>{1, 2, 3}) == Result::Other);
  REQUIRE(consume(std::istringstream{"other"s}) == Result::Other);
}

