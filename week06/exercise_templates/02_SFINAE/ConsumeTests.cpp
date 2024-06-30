#include "Consume.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Consume With Integer Arguments Return Result::Integer", "[SFINAE Suite]") {
  REQUIRE(consume(1) == Result::Integer);
  REQUIRE(consume(1l) == Result::Integer);
  REQUIRE(consume(1ll) == Result::Integer);
  REQUIRE(consume(1u) == Result::Integer);
  REQUIRE(consume(1ul) == Result::Integer);
  REQUIRE(consume(1ull) == Result::Integer);
}

TEST_CASE("Consume With Float Arguments Return Result::Float", "[SFINAE Suite]") {
  REQUIRE(consume(1.0f) == Result::Float);
  REQUIRE(consume(1.0) == Result::Float);
  REQUIRE(consume(1.0l) == Result::Float);
}

TEST_CASE("Consume With Float Arguments Return Result::Other", "[SFINAE Suite]") {
  using namespace std::string_literals;
  REQUIRE(consume_b("other"s) == Result::Other);
  REQUIRE(consume_b(std::vector<int>{1, 2, 3}) == Result::Other);
  REQUIRE(consume_b(std::istringstream{"other"s}) == Result::Other);
}


TEST_CASE("bConsume With Integer Arguments Return Result::Integer", "[SFINAE Suite]") {
  REQUIRE(consume_b(1) == Result::Integer);
  REQUIRE(consume_b(1l) == Result::Integer);
  REQUIRE(consume_b(1ll) == Result::Integer);
  REQUIRE(consume_b(1u) == Result::Integer);
  REQUIRE(consume_b(1ul) == Result::Integer);
  REQUIRE(consume_b(1ull) == Result::Integer);
}

TEST_CASE("bConsume With Float Arguments Return Result::Float", "[SFINAE Suite]") {
  REQUIRE(consume_b(1.0f) == Result::Float);
  REQUIRE(consume_b(1.0) == Result::Float);
  REQUIRE(consume_b(1.0l) == Result::Float);
}

TEST_CASE("bConsume With Float Arguments Return Result::Other", "[SFINAE Suite]") {
  using namespace std::string_literals;
  REQUIRE(consume_b("other"s) == Result::Other);
  REQUIRE(consume_b(std::vector<int>{1, 2, 3}) == Result::Other);
  REQUIRE(consume_b(std::istringstream{"other"s}) == Result::Other);
}

TEST_CASE("cConsume With Integer Arguments Return Result::Integer", "[SFINAE Suite]") {
  REQUIRE(consume_c(1) == Result::Integer);
  REQUIRE(consume_c(1l) == Result::Integer);
  REQUIRE(consume_c(1ll) == Result::Integer);
  REQUIRE(consume_c(1u) == Result::Integer);
  REQUIRE(consume_c(1ul) == Result::Integer);
  REQUIRE(consume_c(1ull) == Result::Integer);
}

TEST_CASE("cConsume With Float Arguments Return Result::Float", "[SFINAE Suite]") {
  REQUIRE(consume_c(1.0f) == Result::Float);
  REQUIRE(consume_c(1.0) == Result::Float);
  REQUIRE(consume_c(1.0l) == Result::Float);
}

TEST_CASE("cConsume With Float Arguments Return Result::Other", "[SFINAE Suite]") {
  using namespace std::string_literals;
  REQUIRE(consume_c("other"s) == Result::Other);
  REQUIRE(consume_c(std::vector<int>{1, 2, 3}) == Result::Other);
  REQUIRE(consume_c(std::istringstream{"other"s}) == Result::Other);
}

