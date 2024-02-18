#include "BoundedBufferDefaultBehaviorSuite.hpp"
#include "BoundedBuffer.hpp"

#include <boost/type_index.hpp>

#include <cute/cute.h>

TEST(test_buffer_constructor_for_capacity_zero_throws) {
//   ASSERT_THROWS(BoundedBuffer<int> buffer{0}, std::invalid_argument);
}

TEST(test_int_buffer_of_capacity_thousand_is_empty) {
//   BoundedBuffer<int> const buffer{1000};
//   ASSERTM("New buffer should be empty", buffer.empty());
}

TEST(test_const_int_buffer_of_capacity_thousand_is_not_full) {
//   BoundedBuffer<int> const buffer{1000};
//   ASSERTM("New buffer should not be full", !buffer.full());
}

TEST(test_int_buffer_of_capacity_thousand_has_size_zero) {
//   BoundedBuffer<int> const buffer{1000};
//   ASSERT_EQUALM("New buffer should be empty", 0, buffer.size());
}

TEST(test_empty_bounded_buffer_throws_on_front) {
//   BoundedBuffer<int> buffer{23};
//   ASSERT_THROWS(buffer.front(), std::logic_error);
}

TEST(test_empty_const_bounded_buffer_throws_on_front) {
//   BoundedBuffer<int> const buffer{23};
//   ASSERT_THROWS(buffer.front(), std::logic_error);
}

TEST(test_empty_bounded_buffer_throws_on_back) {
//   BoundedBuffer<int> buffer{23};
//   ASSERT_THROWS(buffer.back(), std::logic_error);
}

TEST(test_empty_const_bounded_buffer_throws_on_back) {
//   BoundedBuffer<int> const buffer{23};
//   ASSERT_THROWS(buffer.back(), std::logic_error);
}

TEST(test_empty_bounded_buffer_throws_on_pop) {
//   BoundedBuffer<int> buffer{23};
//   ASSERT_THROWS(buffer.pop(), std::logic_error);
}

TEST(test_full_bounded_buffer_throws_on_push_const_lvalue) {
//   BoundedBuffer<int> buffer{1};
//   int const lvalue{23};
//   buffer.push(lvalue);
//   ASSERT_THROWS(buffer.push(lvalue), std::logic_error);
}

TEST(test_full_bounded_buffer_throws_on_push_rvalue) {
//   BoundedBuffer<int> buffer{1};
//   int const lvalue{23};
//   buffer.push(lvalue);
//   ASSERT_THROWS(buffer.push(23), std::logic_error);
}

auto make_suite_bounded_buffer_default_behavior_suite() -> cute::suite {
  return cute::suite{"BoundedBuffer Default Behavior Suite",
                     {
                         test_int_buffer_of_capacity_thousand_is_empty,
                         test_buffer_constructor_for_capacity_zero_throws,
                         test_const_int_buffer_of_capacity_thousand_is_not_full,
                         test_int_buffer_of_capacity_thousand_has_size_zero,
                         test_empty_bounded_buffer_throws_on_front,
                         test_empty_const_bounded_buffer_throws_on_front,
                         test_empty_bounded_buffer_throws_on_back,
                         test_empty_const_bounded_buffer_throws_on_back,
                         test_empty_bounded_buffer_throws_on_pop,
                         test_full_bounded_buffer_throws_on_push_const_lvalue,
                         test_full_bounded_buffer_throws_on_push_rvalue,
                     }};
}
