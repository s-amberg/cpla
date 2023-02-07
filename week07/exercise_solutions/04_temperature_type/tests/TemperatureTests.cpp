#include "Temperature.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

using units::Temperature;
using namespace units::tags;
using namespace units::literals;

template <typename scale>
constexpr auto willWaterFreeze(Temperature<scale> const& temperature) -> bool {
  return units::temperatureCast<Celcius>(temperature) <=
         Temperature<Celcius>{0.0};
}

TEST(waterFreezesAt273Kelvin) {
  ASSERT(willWaterFreeze(Temperature<Kelvin>{273}));
}

TEST(waterFreezesAt0Celcius) {
  ASSERT(willWaterFreeze(Temperature<Celcius>{0}));
}

TEST(waterFreezesAt32Fahrenheit) {
  ASSERT(willWaterFreeze(Temperature<Fahrenheit>{32}));
}

TEST(testCelciusToKelvin) {
  static_assert(20_C == 293.15_K);
  ASSERT_EQUAL(20_C, 293.15_K);
}

TEST(testKelvinToCelcius) {
  static_assert(20_K == -253.15_C);
  ASSERT_EQUAL(20_K, -253.15_C);
}

TEST(testFahrenheitToCelcius) {
  static_assert(20_F == -6.6667_C);
  ASSERT_EQUAL(20_F, -6.6667_C);
}

TEST(testCelciusToFahrenheit) {
  static_assert(20_C == 68.0_F);
  ASSERT_EQUAL(20_C, 68.0_F);
}

TEST(testKelvinToFahrenheit) {
  static_assert(20_K == -423.67_F);
  ASSERT_EQUAL(20_K, -423.67_F);
}

TEST(testFahrenheitToKelvin) {
  static_assert(20_F == 266.4833_K);
  ASSERT_EQUAL(20_F, 266.4833_K);
}

auto main(int argc, char const* argv[]) -> int {
  auto suite = cute::suite{"Temperature Tests",
                           {
                               waterFreezesAt273Kelvin,
                               waterFreezesAt0Celcius,
                               waterFreezesAt32Fahrenheit,
                               testCelciusToKelvin,
                               testKelvinToCelcius,
                               testFahrenheitToCelcius,
                               testCelciusToFahrenheit,
                               testKelvinToFahrenheit,
                               testFahrenheitToKelvin,
                           }};

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}