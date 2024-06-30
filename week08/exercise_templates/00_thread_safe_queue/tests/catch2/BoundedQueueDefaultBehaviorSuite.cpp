#include "BoundedQueue.hpp"

#include <boost/type_index.hpp>
#include <catch2/catch_test_macros.hpp>

#include <chrono>
#include <stdexcept>
#include <utility>

TEST_CASE("Queue constructor for capacity zero throws", "[Default Behavior Suite]") {
  REQUIRE_THROWS_AS(BoundedQueue<int>{0}, std::invalid_argument);
}

TEST_CASE("Int queue of capacity thousand is empty", "[Default Behavior Suite]") {
  BoundedQueue<int> const queue{1000};
  REQUIRE(queue.empty());
}

TEST_CASE("Const int queue of capacity thousand is not full", "[Default Behavior Suite]") {
  BoundedQueue<int> const queue{1000};
  REQUIRE_FALSE(queue.full());
}

TEST_CASE("Int queue of capacity thousand has size zero", "[Default Behavior Suite]") {
  BoundedQueue<int> const queue{1000};
  REQUIRE(queue.size() == 0);
}

TEST_CASE("Empty bounded queue returns false on try_pop", "[Default Behavior Suite]") {
  BoundedQueue<int> queue{23};
  int val{};
  REQUIRE_FALSE(queue.try_pop(val));
}

TEST_CASE("Full bounded queue returns false on try_push const lvalue", "[Default Behavior Suite]") {
  BoundedQueue<int> queue{1};
  int const lvalue{23};
  queue.push(lvalue);
  REQUIRE_FALSE(queue.try_push(lvalue));
}

TEST_CASE("Full bounded queue returns false on try_push rvalue", "[Default Behavior Suite]") {
  BoundedQueue<int> queue{1};
  int lvalue{23};
  queue.push(lvalue);
  REQUIRE_FALSE(queue.try_push(std::move(lvalue)));
}

using namespace std::chrono_literals;

TEST_CASE("Empty bounded queue returns false on try_pop_for", "[Default Behavior Suite]") {
  BoundedQueue<int> queue{23};
  int val{};
  REQUIRE_FALSE(queue.try_pop_for(val, 1ns));
}

TEST_CASE("Full bounded queue returns false on try_push_for const lvalue", "[Default Behavior Suite]") {
  BoundedQueue<int> queue{1};
  int const lvalue{23};
  queue.push(lvalue);
  REQUIRE_FALSE(queue.try_push_for(lvalue, 1ns));
}
