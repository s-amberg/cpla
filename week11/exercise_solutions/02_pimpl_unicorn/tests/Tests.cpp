#include "CreateFreddy.hpp"
#include "Unicorn.hpp"

#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <string>
#include <utility>

TEST_CASE("Copy Assign Unicorn") {
  // We can't have that anymore, unless we implement it explicitly

  //   using namespace std::string_literals;
  //   auto const freddy = createFreddy();
  //   Unicorn other{"henry"s, "blue"s};
  //   other = freddy;
  //   REQUIRE(freddy == other);
}

TEST_CASE("Copy Construct Unicorn") {
  // We can't have that anymore, unless we implement it explicitly

  //   auto const freddy = createFreddy();
  //   auto const copy{freddy};
  //   REQUIRE(freddy == copy);
}

TEST_CASE("Create Unicorn") {
  Unicorn const freddy = createFreddy();
  REQUIRE(freddy == freddy);
}

TEST_CASE("Move Assign Unicorn") {
  using namespace std::string_literals;
  auto freddy = createFreddy();
  Unicorn other{"henry", "blue"};
  other = std::move(freddy);
  REQUIRE(createFreddy() == other);
}

TEST_CASE("Move Construct Unicorn") {
  auto freddy = createFreddy();
  auto moved{std::move(freddy)};
  REQUIRE(createFreddy() == moved);
}

TEST_CASE("Unicorn Fly") {
  using namespace std::string_literals;
  auto const freddy = createFreddy();
  std::ostringstream out{};
  freddy.fly(out);
  REQUIRE(out.str() == "freddy flies at 24m\n"s);
}

TEST_CASE("Unicorn Glitter") {
  using namespace std::string_literals;
  auto const freddy = createFreddy();
  std::ostringstream out{};
  freddy.glitter(out);
  REQUIRE(out.str() == "freddy glitters beautifully\n"s);
}
