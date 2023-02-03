#include "BetterValueHolder.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <typeindex>
#include <utility>

TEST(testFibo0) {
  value_holder i{};  // empty
  ASSERTM("value is undefined", !static_cast<bool>(i));
}
TEST(testWithValue) {
  value_holder v{42};
  ASSERTM("value is defined", bool(v));
  ASSERT_EQUAL(42, v.get<int>());
  v.clear();
  ASSERT_THROWS(v.get<int>(), bad_get<int>);
}
TEST(testWithWrongGet) {
  value_holder v{42};
  ASSERT_EQUAL(42, v.get<int>());
  ASSERT_THROWS(v.get<short>(), bad_get<short>);
}

TEST(testWithReassign) {
  using namespace std::string_literals;
  value_holder i{};
  ASSERTM("undefined value", !bool(i));
  i = 42;
  ASSERTM("defined value", bool(i));
  ASSERT_EQUAL(42, i.get<int>());
  i = "hallo"s;
  ASSERT_EQUAL("hallo"s, i.get<std::string>());
  i.clear();
  ASSERT_THROWS(i.get<int>(), bad_get<int>);
}
TEST(testWithCopyCtor) {
  value_holder i{42};
  value_holder j{i};
  ASSERT_EQUAL(42, j.get<int>());
}
TEST(testWithCopyAssign) {
  value_holder i{42};
  value_holder j{};
  j = i;
  ASSERT_EQUAL(42, j.get<int>());
}

struct tracer {
  tracer(std::ostream& os) : out{os} {
    out.get() << "tracer ctor" << std::endl;
  }
  ~tracer() { out.get() << "~tracer" << std::endl; }
  tracer(tracer&& rhs) : out{rhs.out} {
    out.get() << "tracer move ctor" << std::endl;
  }
  tracer& operator=(tracer&& rhs) {
    out = rhs.out;
    out.get() << "tracer move assign" << std::endl;
    return *this;
  }
  tracer(tracer const& rhs) : out{rhs.out} {
    out.get() << "tracer copy ctor" << std::endl;
  }
  tracer& operator=(tracer const& rhs) {
    out = rhs.out;
    out.get() << "tracer copy assign" << std::endl;
    return *this;
  }
  std::reference_wrapper<std::ostream> out;
};
TEST(testDtor) {
  std::ostringstream os{};
  { value_holder sh{tracer{os}}; }
  ASSERT_EQUAL("tracer ctor\ntracer move ctor\n~tracer\n~tracer\n", os.str());
}

TEST(testMoveCtor) {
  std::ostringstream os{};
  value_holder sh{tracer{os}};
  ASSERTM("defined value", bool(sh));
  sh = value_holder{};
  ASSERTM("no defined value", !sh);
  ASSERT_EQUAL("tracer ctor\ntracer move ctor\n~tracer\n~tracer\n", os.str());
}

TEST(testLvalueArgumentForCtor) {
  std::ostringstream os{};
  tracer tr{os};
  value_holder sh{tr};
  ASSERTM("defined value", bool(sh));
  sh = value_holder{};
  ASSERTM("no defined value", !sh);
  ASSERT_EQUAL("tracer ctor\ntracer copy ctor\n~tracer\n", os.str());
}

TEST(testLvalueArgumentForAssignment) {
  std::ostringstream os{};
  tracer tr{os};
  value_holder sh{};
  sh = tr;
  ASSERTM("defined value", bool(sh));
  sh = value_holder{};
  ASSERTM("no defined value", !sh);
  ASSERT_EQUAL("tracer ctor\ntracer copy ctor\n~tracer\n", os.str());
}

auto main(int argc, char const* argv[]) -> int {
  auto suite = cute::suite{"BetterValueHolder Tests",
                           {
                               testFibo0,
                               testWithValue,
                               testWithReassign,
                               testMoveCtor,
                               testDtor,
                               testLvalueArgumentForAssignment,
                               testLvalueArgumentForCtor,
                               testWithWrongGet,
                               testWithCopyCtor,
                               testWithCopyAssign,
                           }};

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}