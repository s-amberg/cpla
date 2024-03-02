

#include "DynArray.hpp"

#include <catch2/catch_test_macros.hpp>

#include <boost/iterator/counting_iterator.hpp>
#include <cstddef>
#include <string>

TEST_CASE("Default Construct DynArray") {
  auto da = DynArray<int>{};
  REQUIRE(da.size() == 0);
  REQUIRE(da.empty());
}

TEST_CASE("Initializerlist-Constructed DynArray Is Not Empty") {
  auto da = DynArray{1u, 2u, 3u, 4u};
  REQUIRE(da.size() == 4);
  REQUIRE(!da.empty());
  REQUIRE(da[0] == 1u);
  REQUIRE(da[-1] == 4u);
  REQUIRE(da[-3] == 2);
  REQUIRE(da[2] == 3);
}

TEST_CASE("Range-Constructed DynArray") {
  auto iter = boost::make_counting_iterator(0.0);
  auto e = boost::make_counting_iterator(11.0);
  auto const da = DynArray(iter, e);
  REQUIRE(da.size() == 11);
  REQUIRE(da.at(1) == 1.0);
  REQUIRE(da.at(-1) == 10.0);
  REQUIRE(da[5] == 5.0);
  REQUIRE(da[-5] == 6.0);
}

TEST_CASE("N-Times Value Constructed DynArray") {
  auto da = DynArray(10u, 3.14);
  REQUIRE(da.size() == 10u);
  REQUIRE(da.at(-1) == 3.14);
}

TEST_CASE("Two Parameter Constructor Ambiguity") {
  DynArray<std::size_t> da(10u, 1u); // must use parentheses
  REQUIRE(da.size() == 10u);
  DynArray<std::size_t> da2{10u, 1u};
  REQUIRE(da2.size() == 2u);
}

TEST_CASE("Sequence Container Functions") {
  auto da = DynArray{1, 2, 3};
  da.push_back(4);
  REQUIRE(da.size() == 4);
  REQUIRE(da.front() == 1);
  REQUIRE(da.back() == 4);
  da.front() = 42;
  REQUIRE(da.front() == 42);
  da.back() = 42;
  REQUIRE(da.back() == 42);
  da.pop_back();
  REQUIRE(da.size() == 3);
}

TEST_CASE("Const Iterator Functions") {
  auto da = DynArray{'a', 'b', 'c'};
  std::string s{da.begin(), da.end()};
  REQUIRE(s == "abc");
}

TEST_CASE("Non-Const Iterator Functions") {
  DynArray<std::string> da{"one", "two"};
  REQUIRE(*da.begin() == "one");
  *da.begin() = "none";
  REQUIRE(*da.begin() == "none");
  *(da.end() - 1) = "on";
  REQUIRE(*(da.begin() + 1) == "on");
}

TEST_CASE("Reverse Iterator Functions") {
  auto da = DynArray{'1', '2', '3', '4'};
  std::string s{da.rbegin(), da.rend()};
  REQUIRE(s == "4321");
}

TEST_CASE("Non-Const Reverse Iterator Functions") {
  auto da = DynArray{4, 3, 2, 1};
  *da.rbegin() = 42;
  REQUIRE(da.at(-1) == 42);
  *(da.rend() - 1) = 42;
  REQUIRE(da[0] == 42);
}

TEST_CASE("Const Iterator Functions Availability") {
  auto da = DynArray{'p', 'e', 't', 'e', 'r'};
  std::string peter{da.cbegin(), da.cend()};
  std::string retep{da.crbegin(), da.crend()};
  REQUIRE(peter == "peter");
  REQUIRE(retep == "retep");
}

TEST_CASE("Resize Available") {
  auto da = DynArray<int>{};
  da.resize(10);
  REQUIRE(da.size() == 10);
  REQUIRE(da[-1] == 0);
}
