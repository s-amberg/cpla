#include "Speed.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

using velocity::Speed;

TEST(overtakePedestrianAt10Kph) {
  ASSERT(isFasterThanWalking(Speed::fromKph(10.0)));
}

TEST(overtakePedestrianAt6dot2Mph) {
  ASSERT(isFasterThanWalking(Speed::fromMph(6.2)));
}

TEST(overtakePedestrianAt2dot8Mps) {
  ASSERT(isFasterThanWalking(Speed::fromMps(2.8)));
}

TEST(testMpsLiteral) {
  using namespace velocity::literals;
  auto const speed = 5.0_mps;
  ASSERT_EQUAL(5.0, speed.toMps());
}

TEST(testKpsLiteral) {
  using namespace velocity::literals;
  auto const speed = 5.0_kph;
  ASSERT_EQUAL(5.0, speed.toKph());
}

TEST(testMphLiteral) {
  using namespace velocity::literals;
  auto const speed = 5.0_mph;
  ASSERT_EQUAL(5.0, speed.toMph());
}

auto main(int argc, char const* argv[]) -> int {
  auto suite = cute::suite{"Speed Tests",
                           {
                               overtakePedestrianAt10Kph,
                               overtakePedestrianAt6dot2Mph,
                               overtakePedestrianAt2dot8Mps,
                               testMpsLiteral,
                               testMphLiteral,
                               testKpsLiteral,
                           }};

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}