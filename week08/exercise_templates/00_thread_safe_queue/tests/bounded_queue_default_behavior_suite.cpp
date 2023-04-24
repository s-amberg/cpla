#include "bounded_queue_default_behavior_suite.hpp"

#include <cute/cute.h>

// #include "BoundedQueue.hpp"
#include <boost/type_index.hpp>
#include <chrono>

TEST(test_queue_constructor_for_capacity_zero_throws) {
  // ASSERT_THROWS(BoundedQueue<int> queue{0}, std::invalid_argument);
}

TEST(test_int_queue_of_capacity_thousand_is_empty) {
  // BoundedQueue<int> const queue{1000};
  // ASSERTM("New queue should be empty", queue.empty());
}

TEST(test_const_int_queue_of_capacity_thousand_is_not_full) {
  // BoundedQueue<int> const queue{1000};
  // ASSERTM("New queue should not be full", !queue.full());
}

TEST(test_int_queue_of_capacity_thousand_has_size_zero) {
  // BoundedQueue<int> const queue{1000};
  // ASSERT_EQUALM("New queue should be empty", 0, queue.size());
}

TEST(test_empty_bounded_queue_returns_false_on_try_pop) {
  // BoundedQueue<int> queue{23};
  // int val{};
  // ASSERT(!queue.try_pop(val));
}

TEST(test_full_bounded_queue_returns_false_on_try_push_const_lvalue) {
  // BoundedQueue<int> queue{1};
  // int const lvalue{23};
  // queue.push(lvalue);
  // ASSERT(!queue.try_push(lvalue));
}
TEST(test_full_bounded_queue_returns_false_on_try_push_rvalue) {
  // BoundedQueue<int> queue{1};
  // int lvalue{23};
  // queue.push(lvalue);
  // ASSERT(!queue.try_push(std::move(lvalue)));
}
using namespace std::chrono_literals;
TEST(test_empty_bounded_queue_returns_false_on_try_pop_for) {
  // BoundedQueue<int> queue{23};
  // int val{};
  // ASSERT(!queue.try_pop_for(val, 1ns));
}

TEST(test_full_bounded_queue_returns_false_on_try_push_for_const_lvalue) {
  // BoundedQueue<int> queue{1};
  // int const lvalue{23};
  // queue.push(lvalue);
  // ASSERT(!queue.try_push_for(lvalue, 1ns));
}

auto make_suite_bounded_queue_default_behavior_suite() -> cute::suite {
  return cute::suite{"BoundedQueue Default Behavior Suite",
                     {
                         test_int_queue_of_capacity_thousand_is_empty,
                         test_queue_constructor_for_capacity_zero_throws,
                         test_const_int_queue_of_capacity_thousand_is_not_full,
                         test_int_queue_of_capacity_thousand_has_size_zero,
                         test_empty_bounded_queue_returns_false_on_try_pop,
                         test_full_bounded_queue_returns_false_on_try_push_const_lvalue,
                         test_full_bounded_queue_returns_false_on_try_push_rvalue,
                         test_empty_bounded_queue_returns_false_on_try_pop_for,
                         test_full_bounded_queue_returns_false_on_try_push_for_const_lvalue,
                     }};
}
