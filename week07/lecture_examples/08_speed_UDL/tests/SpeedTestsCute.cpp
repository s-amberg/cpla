#include "Speed.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

using velocity::Speed;
using namespace velocity::tags;
using namespace velocity::literals;

template <typename Unit>
auto isFasterThanWalking(Speed<Unit> speed) -> bool {
  return velocity::speedCast<Kph>(speed) > 5.0_kph;
}

TEST(overtakePedestrianAt10Kph) {
  ASSERT(isFasterThanWalking(10.0_kph));
}

TEST(overtakePedestrianAt6dot2Mph) {
  ASSERT(isFasterThanWalking(6.2_mph));
}

TEST(overtakePedestrianAt2dot8Mps) {
  ASSERT(isFasterThanWalking(2.8_mps));
}

TEST(testConversionFromKphToMph) {
  ASSERT_EQUAL(1.60934_kph, 1.0_mph);
}

TEST(testConversionFromMphToKph) {
  ASSERT_EQUAL(1.0_mph, 1.60934_kph);
}

TEST(testConversionFromKphToMps) {
  ASSERT_EQUAL(3.6_kph, 1.0_mps);
}

TEST(testConversionFromMpsToKph) {
  ASSERT_EQUAL(1.0_mps, 3.6_kph);
}

TEST(testConversionFromMphToMps) {
  ASSERT_EQUAL(2.23694_mph, 1.0_mps);
}

TEST(testConversionFromMpsToMph) {
  ASSERT_EQUAL(1.0_mps, 2.23694_mph);
}

TEST(testSelfEquality) {
  ASSERT_EQUAL(1.0_kph, 1.0_kph);
}

auto main(int argc, char const* argv[]) -> int {
  auto suite = cute::suite{"Speed with Tags Tests",
                           {
                               overtakePedestrianAt10Kph,
                               overtakePedestrianAt6dot2Mph,
                               overtakePedestrianAt2dot8Mps,
                               testConversionFromKphToMph,
                               testConversionFromMphToKph,
                               testConversionFromKphToMps,
                               testConversionFromMpsToKph,
                               testConversionFromMphToMps,
                               testConversionFromMpsToMph,
                               testSelfEquality,
                           }};

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}