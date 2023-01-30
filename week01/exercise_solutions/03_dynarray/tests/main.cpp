#include "dynArray.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

#include <boost/iterator/counting_iterator.hpp>

TEST(defaultconstructdynarray) {
  auto da = DynArray<int>{};
  ASSERT_EQUAL(0, da.size());
  ASSERT(da.empty());
}

TEST(initializerlistconstructeddynarrayisNotEmpty) {
  auto da = DynArray{1u, 2u, 3u, 4u};
  ASSERT_EQUAL(4, da.size());
  ASSERT(!da.empty());
  ASSERT_EQUAL(1u, da[0]);
  ASSERT_EQUAL(4u, da[-1]);
  ASSERT_EQUAL(2, da[-3]);
  ASSERT_EQUAL(3, da[2]);
}

TEST(rangeconstructeddynarray) {
  auto iter = boost::make_counting_iterator(0.0);
  auto e = boost::make_counting_iterator(11.0);
  auto const da = DynArray(iter, e);
  ASSERT_EQUAL(11, da.size());
  ASSERT_EQUAL(1.0, da.at(1));
  ASSERT_EQUAL(10.0, da.at(-1));
  ASSERT_EQUAL(5.0, da[5]);
  ASSERT_EQUAL(6.0, da[-5]);
}

TEST(n_times_value_constructeddynarray) {
  auto da = DynArray(10u, 3.14);
  ASSERT_EQUAL(10u, da.size());
  ASSERT_EQUAL(3.14, da.at(-1));
}

TEST(testtwoparaemterconstructorambiguity) {
  DynArray<size_t> da(10u, 1u); // must use parentheses
  ASSERT_EQUAL(10u, da.size());
}

// the following is a lazy and bad test case, because it tests too much in one
TEST(sequencecontainerfunctions) {
  auto da = DynArray{1, 2, 3};
  da.push_back(4);
  ASSERT_EQUAL(4, da.size());
  ASSERT_EQUAL(1, da.front());
  ASSERT_EQUAL(4, da.back());
  da.front() = 42;
  ASSERT_EQUAL(42, da.front());
  da.back() = 42;
  ASSERT_EQUAL(42, da.back());
  da.pop_back();
  ASSERT_EQUAL(3, da.size());
}

TEST(const_iterator_functions) {
  auto da = DynArray{'a', 'b', 'c'};
  std::string s{da.begin(), da.end()};
  ASSERT_EQUAL("abc", s);
}

TEST(nonconst_iterator_functions) {
  DynArray<std::string> da{"one", "two"};
  ASSERT_EQUAL("one", *da.begin());
  *da.begin() = "none";
  ASSERT_EQUAL("none", *da.begin());
  *(da.end() - 1) = "on";
  ASSERT_EQUAL("on", *(da.begin() + 1));
}

TEST(reverse_iterator_functions) {
  auto da = DynArray{'1', '2', '3', '4'};
  std::string s{da.rbegin(), da.rend()};
  ASSERT_EQUAL("4321", s);
}

TEST(nonconst_reverse_iterator_functions) {
  auto da = DynArray{4, 3, 2, 1};
  *da.rbegin() = 42;
  ASSERT_EQUAL(42, da.at(-1));
  *(da.rend() - 1) = 42;
  ASSERT_EQUAL(42, da[0]);
}

TEST(const_iterator_functions_availability) {
  auto da = DynArray{'p', 'e', 't', 'e', 'r'};
  std::string peter{da.cbegin(), da.cend()};
  std::string retep{da.crbegin(), da.crend()};
  ASSERT_EQUAL("peter", peter);
  ASSERT_EQUAL("retep", retep);
}

TEST(resizeAvailable) {
  auto da = DynArray<int>{};
  da.resize(10);
  ASSERT_EQUAL(10, da.size());
  ASSERT_EQUAL(0, da[-1]);
}

auto main(int argc, char const *argv[]) -> int {
  auto suite = cute::suite{
    "DynArray<T> Tests",
    {
      defaultconstructdynarray,
      initializerlistconstructeddynarrayisNotEmpty,
      rangeconstructeddynarray,
      sequencecontainerfunctions,
      const_iterator_functions,
      nonconst_iterator_functions,
      reverse_iterator_functions,
      nonconst_reverse_iterator_functions,
      const_iterator_functions_availability,
      resizeAvailable,
      n_times_value_constructeddynarray,
      testtwoparaemterconstructorambiguity,
    }
  };

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}
