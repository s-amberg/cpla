#include "BoundedBuffer.hpp"

#include "NTimes.hpp"

#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <vector>

using namespace cpp_advanced::times_literal;
using namespace buffy;

TEST_CASE("BoundedBuffer is not empty after push(rvalue)", "[Content Suite]") {
  BoundedBuffer<int, 5> buffer{};
  buffer.push(5);
  REQUIRE_FALSE(buffer.empty());
}

TEST_CASE("BoundedBuffer is not empty after push(lvalue)", "[Content Suite]") {
  BoundedBuffer<int, 5> buffer{};
  int const lvalue{5};
  buffer.push(lvalue);
  REQUIRE_FALSE(buffer.empty());
}

TEST_CASE("BoundedBuffer is empty after one push(rvalue) and pop()", "[Content Suite]") {
  BoundedBuffer<int, 5> buffer{};
  buffer.push(5);
  buffer.pop();
  REQUIRE(buffer.empty());
}

TEST_CASE("BoundedBuffer of size two is full after two push(rvalue)s", "[Content Suite]") {
  BoundedBuffer<int, 2> buffer{};
  buffer.push(5);
  buffer.push(5);
  REQUIRE(buffer.full());
}

TEST_CASE("BoundedBuffer size() is one after push(rvalue)", "[Content Suite]") {
  BoundedBuffer<int, 2> buffer{};
  buffer.push(1);
  REQUIRE(buffer.size() == 1);
}

TEST_CASE("BoundedBuffer size() is fifty after fifty push(rvalue)s", "[Content Suite]") {
  BoundedBuffer<int, 75> buffer{};
  50_times([&]() { buffer.push(5); });
  REQUIRE(buffer.size() == 50);
}

TEST_CASE("BoundedBuffer front() gets element of push(rvalue)", "[Content Suite]") {
  BoundedBuffer<int, 5> buffer{};
  buffer.push(5);
  REQUIRE(buffer.front() == 5);
}

TEST_CASE("BoundedBuffer back() gets element of push(rvalue)", "[Content Suite]") {
  BoundedBuffer<int, 5> buffer{};
  buffer.push(5);
  REQUIRE(buffer.back() == 5);
}

TEST_CASE("BoundedBuffer front() gets first element of push(rvalue)s", "[Content Suite]") {
  BoundedBuffer<int, 5> buffer{};
  buffer.push(1);
  buffer.push(2);
  REQUIRE(buffer.front() == 1);
}

TEST_CASE("BoundedBuffer back() gets last element of two push(rvalue)s", "[Content Suite]") {
  BoundedBuffer<int, 5> buffer{};
  buffer.push(1);
  buffer.push(2);
  REQUIRE(buffer.back() == 2);
}

TEST_CASE("BoundedBuffer front() throws after push(rvalue) and pop()", "[Content Suite]") {
  BoundedBuffer<int, 5> buffer{};
  buffer.push(5);
  buffer.pop();
  REQUIRE_THROWS_AS(buffer.front(), std::logic_error);
}

TEST_CASE("BoundedBuffer back() throws after push(rvalue) and pop()", "[Content Suite]") {
  BoundedBuffer<int, 5> buffer{};
  buffer.push(5);
  buffer.pop();
  REQUIRE_THROWS_AS(buffer.back(), std::logic_error);
}

TEST_CASE("BoundedBuffer const front() gets element of push(rvalue)", "[Content Suite]") {
  BoundedBuffer<int, 5> buffer{};
  buffer.push(5);
  auto const &constBuffer = buffer;
  REQUIRE(constBuffer.front() == 5);
}

TEST_CASE("BoundedBuffer const back() gets element of push(rvalue)", "[Content Suite]") {
  BoundedBuffer<int, 5> buffer{};
  buffer.push(5);
  auto const &constBuffer = buffer;
  REQUIRE(constBuffer.back() == 5);
}

TEST_CASE("BoundedBuffer const front() gets first element of push(rvalue)s", "[Content Suite]") {
  BoundedBuffer<int, 5> buffer{};
  buffer.push(1);
  buffer.push(2);
  auto const &constBuffer = buffer;
  REQUIRE(constBuffer.front() == 1);
}

TEST_CASE("BoundedBuffer const back() gets last element of two push(rvalue)s", "[Content Suite]") {
  BoundedBuffer<int, 5> buffer{};
  buffer.push(1);
  buffer.push(2);
  auto const &constBuffer = buffer;
  REQUIRE(constBuffer.back() == 2);
}

TEST_CASE("BoundedBuffer const front() throws after push(rvalue) and pop()", "[Content Suite]") {
  BoundedBuffer<int, 5> buffer{};
  buffer.push(5);
  buffer.pop();
  auto const &constBuffer = buffer;
  REQUIRE_THROWS_AS(constBuffer.front(), std::logic_error);
}

TEST_CASE("BoundedBuffer const back() throws after push(rvalue) and pop()", "[Content Suite]") {
  BoundedBuffer<int, 5> buffer{};
  buffer.push(5);
  buffer.pop();
  auto const &constBuffer = buffer;
  REQUIRE_THROWS_AS(constBuffer.back(), std::logic_error);
}

TEST_CASE("BoundedBuffer front()s in sequence of push()/pop()", "[Content Suite]") {
  BoundedBuffer<int, 5> buffer{};
  std::vector<int> frontValues{}, expectedValues{1, 1, 1, 2, 2, 3, 4, 4, 5};
  buffer.push(1);
  frontValues.push_back(buffer.front());
  buffer.push(2);
  frontValues.push_back(buffer.front());
  buffer.push(3);
  frontValues.push_back(buffer.front());
  buffer.pop();
  frontValues.push_back(buffer.front());
  buffer.push(4);
  frontValues.push_back(buffer.front());
  buffer.pop();
  frontValues.push_back(buffer.front());
  buffer.pop();
  frontValues.push_back(buffer.front());
  buffer.push(5);
  frontValues.push_back(buffer.front());
  buffer.pop();
  frontValues.push_back(buffer.front());
  REQUIRE(expectedValues == frontValues);
}

TEST_CASE("BoundedBuffer wrap around behavior of front()", "[Content Suite]") {
  BoundedBuffer<int, 3> buffer{};
  std::vector<int> frontValues{}, expectedValues{1, 1, 2, 2, 2, 3, 4, 4, 5, 5, 5, 6, 7};
  buffer.push(1);
  frontValues.push_back(buffer.front());
  buffer.push(2);
  frontValues.push_back(buffer.front());
  buffer.pop();
  frontValues.push_back(buffer.front());
  buffer.push(3);
  frontValues.push_back(buffer.front());
  buffer.push(4);
  frontValues.push_back(buffer.front());
  buffer.pop();
  frontValues.push_back(buffer.front());
  buffer.pop();
  frontValues.push_back(buffer.front());
  buffer.push(5);
  frontValues.push_back(buffer.front());
  buffer.pop();
  frontValues.push_back(buffer.front());
  buffer.push(6);
  frontValues.push_back(buffer.front());
  buffer.push(7);
  frontValues.push_back(buffer.front());
  buffer.pop();
  frontValues.push_back(buffer.front());
  buffer.pop();
  frontValues.push_back(buffer.front());
  REQUIRE(expectedValues == frontValues);
}

TEST_CASE("BoundedBuffer wrap around behavior of back()", "[Content Suite]") {
  BoundedBuffer<int, 3> buffer{};
  std::vector<int> backValues{}, expectedValues{1, 2, 2, 3, 4, 4, 4, 5, 5, 6, 7, 7, 7};
  buffer.push(1);
  backValues.push_back(buffer.back());
  buffer.push(2);
  backValues.push_back(buffer.back());
  buffer.pop();
  backValues.push_back(buffer.back());
  buffer.push(3);
  backValues.push_back(buffer.back());
  buffer.push(4);
  backValues.push_back(buffer.back());
  buffer.pop();
  backValues.push_back(buffer.back());
  buffer.pop();
  backValues.push_back(buffer.back());
  buffer.push(5);
  backValues.push_back(buffer.back());
  buffer.pop();
  backValues.push_back(buffer.back());
  buffer.push(6);
  backValues.push_back(buffer.back());
  buffer.push(7);
  backValues.push_back(buffer.back());
  buffer.pop();
  backValues.push_back(buffer.back());
  buffer.pop();
  backValues.push_back(buffer.back());
  REQUIRE(expectedValues == backValues);
}

TEST_CASE("BoundedBuffer swap() has argument content", "[Content Suite]") {
  std::vector<int> frontValues{}, expectedValues{1, 2, 3};
  BoundedBuffer<int, 5> buffer{}, otherBuffer{};
  buffer.push(1);
  buffer.push(2);
  buffer.push(3);
  otherBuffer.swap(buffer);
  3_times([&]() {
    frontValues.push_back(otherBuffer.front());
    otherBuffer.pop();
  });
  REQUIRE(expectedValues == frontValues);
}

TEST_CASE("BoundedBuffer swap() argument has this content", "[Content Suite]") {
  std::vector<int> frontValues{}, expectedValues{1, 2, 3};
  BoundedBuffer<int, 5> buffer{}, otherBuffer{};
  buffer.push(1);
  buffer.push(2);
  buffer.push(3);
  buffer.swap(otherBuffer);
  3_times([&]() {
    frontValues.push_back(otherBuffer.front());
    otherBuffer.pop();
  });
  REQUIRE(expectedValues == frontValues);
}
