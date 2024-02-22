#include "Speed.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

using velocity::Speed;
using namespace velocity::tags;

template <typename Unit>
auto isFasterThanWalking(Speed<Unit> speed) -> bool {
  return velocity::speedCast<Kph>(speed) > Speed<Kph>{5.0};
}

TEST(overtakePedestrianAt10Kph) {
  ASSERT(isFasterThanWalking(Speed<Kph>{10.0}));
}

TEST(overtakePedestrianAt6dot2Mph) {
  ASSERT(isFasterThanWalking(Speed<Mph>{6.2}));
}

TEST(overtakePedestrianAt2dot8Mps) {
  ASSERT(isFasterThanWalking(Speed<Mps>{2.8}));
}

TEST(testConversionFromKphToMph) {
  ASSERT_EQUAL(Speed<Kph>{1.60934}, Speed<Mph>{1.0});
}

TEST(testConversionFromMphToKph) {
  ASSERT_EQUAL(Speed<Mph>{1.0}, Speed<Kph>{1.60934});
}

TEST(testConversionFromKphToMps) {
  ASSERT_EQUAL(Speed<Kph>{3.6}, Speed<Mps>{1.0});
}

TEST(testConversionFromMpsToKph) {
  ASSERT_EQUAL(Speed<Mps>{1.0}, Speed<Kph>{3.6});
}

TEST(testConversionFromMphToMps) {
  ASSERT_EQUAL(Speed<Mph>{2.23694}, Speed<Mps>{1.0});
}

TEST(testConversionFromMpsToMph) {
  ASSERT_EQUAL(Speed<Mps>{1.0}, Speed<Mph>{2.23694});
}

TEST(testSelfEquality) {
  ASSERT_EQUAL(Speed<Kph>{1.0}, Speed<Kph>{1.0});
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