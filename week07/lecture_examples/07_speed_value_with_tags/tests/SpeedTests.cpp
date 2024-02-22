#include "Speed.hpp"

#include <catch2/catch_test_macros.hpp>

using velocity::Speed;
using namespace velocity::tags;

template <typename Unit>
auto isFasterThanWalking(Speed<Unit> speed) -> bool {
  return velocity::speedCast<Kph>(speed) > Speed<Kph>{5.0};
}


TEST_CASE("Overtake Pedestrian At 10 Kph", "[Speed Suite]") {
  REQUIRE(isFasterThanWalking(Speed<Kph>{10.0}));
}

TEST_CASE("Overtake Pedestrian At 6.2 Mph", "[Speed Suite]") {
  REQUIRE(isFasterThanWalking(Speed<Mph>{6.2}));
}

TEST_CASE("Overtake Pedestrian At 2.8 Mps", "[Speed Suite]") {
  REQUIRE(isFasterThanWalking(Speed<Mps>{2.8}));
}

TEST_CASE("Conversion From Kph To Mph", "[Speed Suite]") {
  REQUIRE(Speed<Kph>{1.60934} == Speed<Mph>{1.0});
}

TEST_CASE("Conversion From Mph To Kph", "[Speed Suite]") {
  REQUIRE(Speed<Mph>{1.0} == Speed<Kph>{1.60934});
}

TEST_CASE("Conversion From Kph To Mps", "[Speed Suite]") {
  REQUIRE(Speed<Kph>{3.6} == Speed<Mps>{1.0});
}

TEST_CASE("Conversion From Mps To Kph", "[Speed Suite]") {
  REQUIRE(Speed<Mps>{1.0} == Speed<Kph>{3.6});
}

TEST_CASE("Conversion From Mph To Mps", "[Speed Suite]") {
  REQUIRE(Speed<Mph>{2.23694} == Speed<Mps>{1.0});
}

TEST_CASE("Conversion From Mps To Mph", "[Speed Suite]") {
  REQUIRE(Speed<Mps>{1.0} == Speed<Mph>{2.23694});
}

TEST_CASE("Self Equality", "[Speed Suite]") {
  REQUIRE(Speed<Kph>{1.0} == Speed<Kph>{1.0});
}
