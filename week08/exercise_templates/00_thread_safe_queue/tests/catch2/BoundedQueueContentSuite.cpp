// #include "BoundedQueue.hpp"

#include "TimesLiteral.hpp"

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

using namespace times::literal;

TEST_CASE("Test queue is not empty after push of rvalue", "[Content Suite]") {
  // BoundedQueue<int> queue{5};
  // queue.push(5);
  // INFO("Queue should not be empty after push");
  // REQUIRE_FALSE(queue.empty());
}

TEST_CASE("Test queue is not empty after push of lvalue", "[Content Suite]") {
  // BoundedQueue<int> queue{5};
  // int const lvalue{5};
  // queue.push(lvalue);
  // INFO("Queue should not be empty after push");
  // REQUIRE_FALSE(queue.empty());
}

TEST_CASE("Test queue is empty after one push and pop", "[Content Suite]") {
  // BoundedQueue<int> queue{5};
  // queue.push(5);
  // queue.pop();
  // INFO("Queue should be empty after one push and pop");
  // REQUIRE(queue.empty());
}

TEST_CASE("Test queue of size two is full after two pushs", "[Content Suite]") {
  // BoundedQueue<int> queue{2};
  // 2_times([&]() { queue.push(5); });
  // INFO("Queue of size two should be full after two pushs");
  // REQUIRE(queue.full());
}

TEST_CASE("Test queue size is one after push", "[Content Suite]") {
  // BoundedQueue<int> queue{2};
  // queue.push(1);
  // REQUIRE(queue.size() == 1);
}

TEST_CASE("Test queue size is fifty after fifty pushs", "[Content Suite]") {
  // BoundedQueue<int> queue{75};
  // 50_times([&]() { queue.push(5); });
  // REQUIRE(queue.size() == 50);
}

TEST_CASE("Test queue pop gets first element of pushs", "[Content Suite]") {
  // BoundedQueue<int> queue{5};
  // queue.push(1);
  // queue.push(2);
  // REQUIRE(queue.pop() == 1);
}

TEST_CASE("Test queue pop in sequence of push", "[Content Suite]") {
  // BoundedQueue<int> queue{5};
  // std::vector<int> frontValues{}, expectedValues{1, 2, 3, 4, 5};
  // queue.push(1);
  // queue.push(2);
  // frontValues.push_back(queue.pop());
  // queue.push(3);
  // queue.push(4);
  // frontValues.push_back(queue.pop());
  // frontValues.push_back(queue.pop());
  // queue.push(5);
  // frontValues.push_back(queue.pop());
  // frontValues.push_back(queue.pop());
  // REQUIRE(frontValues == expectedValues);
}

TEST_CASE("Test queue wrap around behavior pop", "[Content Suite]") {
  // BoundedQueue<int> queue{3};
  // std::vector<int> frontValues{}, expectedValues{1, 2, 3, 4, 5, 6, 7};
  // queue.push(1);
  // queue.push(2);
  // frontValues.push_back(queue.pop());
  // frontValues.push_back(queue.pop());
  // queue.push(3);
  // queue.push(4);
  // queue.push(5);
  // frontValues.push_back(queue.pop());
  // frontValues.push_back(queue.pop());
  // frontValues.push_back(queue.pop());
  // queue.push(6);
  // queue.push(7);
  // frontValues.push_back(queue.pop());
  // frontValues.push_back(queue.pop());
  // REQUIRE(frontValues == expectedValues);
}

TEST_CASE("Test queue after swap this has argument content", "[Content Suite]") {
  // std::vector<int> frontValues{}, expectedValues{1, 2, 3};
  // BoundedQueue<int> queue{5}, otherQueue{5};
  // queue.push(1);
  // queue.push(2);
  // queue.push(3);
  // otherQueue.swap(queue);
  // 3_times([&]() { frontValues.push_back(otherQueue.pop()); });
  // REQUIRE(frontValues == expectedValues);
}

TEST_CASE("Test queue after swap argument has this content", "[Content Suite]") {
  // std::vector<int> frontValues{}, expectedValues{1, 2, 3};
  // BoundedQueue<int> queue{5}, otherQueue{5};
  // queue.push(1);
  // queue.push(2);
  // queue.push(3);
  // queue.swap(otherQueue);
  // 3_times([&]() { frontValues.push_back(otherQueue.pop()); });
  // REQUIRE(frontValues == expectedValues);
}
