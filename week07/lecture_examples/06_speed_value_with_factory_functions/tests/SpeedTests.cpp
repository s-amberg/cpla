#include "Speed.hpp"

#include <catch2/catch_test_macros.hpp>

using velocity::Speed;

TEST_CASE("Overtake Pedestrian At 10 Kph", "[Speed Suite]") {
  REQUIRE(isFasterThanWalking(Speed::fromKph(10.0)));
}

TEST_CASE("Overtake Pedestrian At 6.2 Mph", "[Speed Suite]") {
  REQUIRE(isFasterThanWalking(Speed::fromMph(6.2)));
}

TEST_CASE("Overtake Pedestrian At 2.8 Mps", "[Speed Suite]") {
  REQUIRE(isFasterThanWalking(Speed::fromMps(2.8)));
}

TEST_CASE("_mps Literal", "[Speed Suite]") {
  using namespace velocity::literals;
  auto const speed = 5.0_mps;
  REQUIRE(speed.toMps() == 5.0);
}

TEST_CASE("_kps Literal", "[Speed Suite]") {
  using namespace velocity::literals;
  auto const speed = 5.0_kph;
  REQUIRE(speed.toKph() == 5.0);
}

TEST_CASE("_mph Literal", "[Speed Suite]") {
  using namespace velocity::literals;
  auto const speed = 5.0_mph;
  REQUIRE(speed.toMph() == 5.0);
}


