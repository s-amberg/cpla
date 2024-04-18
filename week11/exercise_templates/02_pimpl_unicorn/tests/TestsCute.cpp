#include "CreateFreddy.hpp"
#include "Unicorn.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

#include <sstream>
#include <string>
#include <utility>

TEST(testCopyAssignUnicorn) {
    using namespace std::string_literals;
    auto const freddy = createFreddy();
    Unicorn other{"henry"s, "blue"s};
    other = freddy;
    ASSERT_EQUAL(freddy, other);
}

TEST(testCopyConstructUnicorn) {
    auto const freddy = createFreddy();
    auto const copy{freddy};
    ASSERT_EQUAL(freddy, copy);
}

TEST(testCreateUnicorn) {
  Unicorn const freddy = createFreddy();
  ASSERT_EQUAL(freddy, freddy);
}

TEST(testMoveAssignUnicorn) {
  using namespace std::string_literals;
  auto freddy = createFreddy();
  Unicorn other{"henry", "blue"};
  other = std::move(freddy);
  ASSERT_EQUAL(createFreddy(), other);
}

TEST(testMoveConstructUnicorn) {
  auto freddy = createFreddy();
  auto moved{std::move(freddy)};
  ASSERT_EQUAL(createFreddy(), moved);
}

TEST(testUnicornFly) {
  using namespace std::string_literals;
  auto const freddy = createFreddy();
  std::ostringstream out{};
  freddy.fly(out);
  ASSERT_EQUAL("freddy flies at 24m\n"s, out.str());
}

TEST(testUnicornGlitter) {
  using namespace std::string_literals;
  auto const freddy = createFreddy();
  std::ostringstream out{};
  freddy.glitter(out);
  ASSERT_EQUAL("freddy glitters beautifully\n"s, out.str());
}

auto main(int argc, char const *argv[]) -> int {
  auto suite = cute::suite{"Unicorn Tests",
                           {
                               testUnicornFly,
                               testUnicornGlitter,
                               testCreateUnicorn,
                               testCopyConstructUnicorn,
                               testMoveConstructUnicorn,
                               testCopyAssignUnicorn,
                               testMoveAssignUnicorn,
                           }};

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}
