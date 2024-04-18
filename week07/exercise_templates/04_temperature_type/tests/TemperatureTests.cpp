#include "Temperature.hpp"

#include <catch2/catch_test_macros.hpp>

// using units::Temperature;
// using namespace units::tags;
// using namespace units::literals;

// template <typename scale>
// constexpr auto willWaterFreeze(Temperature<scale> const& temperature) -> bool {
//   return units::temperatureCast<Celcius>(temperature) <=
//          Temperature<Celcius>{0.0};
// }

TEST_CASE("waterFreezesAt273Kelvin", "[Temperature Suite]") {
  // REQUIRE(willWaterFreeze(Temperature<Kelvin>{273}));
}

TEST_CASE("waterFreezesAt0Celcius", "[Temperature Suite]") {
  // REQUIRE(willWaterFreeze(Temperature<Celcius>{0}));
}

TEST_CASE("waterFreezesAt32Fahrenheit", "[Temperature Suite]") {
  // REQUIRE(willWaterFreeze(Temperature<Fahrenheit>{32}));
}

TEST_CASE("testCelciusToKelvin", "[Temperature Suite]") {
  // static_assert(20_C == 293.15_K);
  // REQUIRE(20_C == 293.15_K);
}

TEST_CASE("testKelvinToCelcius", "[Temperature Suite]") {
  // static_assert(20_K == -253.15_C);
  // REQUIRE(20_K == -253.15_C);
}

TEST_CASE("testFahrenheitToCelcius", "[Temperature Suite]") {
  // static_assert(20_F == -6.6667_C);
  // REQUIRE(20_F == -6.6667_C);
}

TEST_CASE("testCelciusToFahrenheit", "[Temperature Suite]") {
  // static_assert(20_C == 68.0_F);
  // REQUIRE(20_C == 68.0_F);
}

TEST_CASE("testKelvinToFahrenheit", "[Temperature Suite]") {
  // static_assert(20_K == -423.67_F);
  // REQUIRE(20_K == -423.67_F);
}

TEST_CASE("testFahrenheitToKelvin", "[Temperature Suite]") {
  // static_assert(20_F == 266.4833_K);
  // REQUIRE(20_F == 266.4833_K);
}
