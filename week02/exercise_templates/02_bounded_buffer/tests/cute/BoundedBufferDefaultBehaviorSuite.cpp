#include "BoundedBuffer.hpp"
#include "BoundedBufferDefaultBehaviorSuite.hpp"


// #include <boost/type_index.hpp>

#include <cute/cute.h>

TEST(test_int_buffer_of_capacity_thousand_is_empty) {
  //	BoundedBuffer<int, 1000> const buffer{};
  //	ASSERTM("New buffer should be empty", buffer.empty());
}

TEST(test_buffer_constructor_for_capacity_zero_is_empty) {
  //	BoundedBuffer<int, 0> const buffer{};
  //	ASSERTM("New buffer should be empty", buffer.empty());
}

TEST(test_const_int_buffer_of_capacity_thousand_is_not_full) {
  //	BoundedBuffer<int, 1000> const buffer{};
  //	ASSERTM("New buffer should not be full", !buffer.full());
}

TEST(test_default_constructed_const_int_buffer_of_size_zero_is_full) {
  //	BoundedBuffer<int, 0> const buffer{};
  //	ASSERTM("New buffer of size 0 should be full", buffer.full());
}

TEST(test_int_buffer_of_capacity_thousand_has_size_zero) {
  //	BoundedBuffer<int, 1000> const buffer{};
  //	ASSERT_EQUALM("New buffer should be empty", 0, buffer.size());
}

TEST(test_default_constructed_const_int_buffer_of_size_zero_has_size_zero) {
  //	BoundedBuffer<int, 0> const buffer{};
  //	ASSERT_EQUALM("New buffer should be empty", 0, buffer.size());
}

TEST(test_empty_bounded_buffer_throws_on_front) {
  //	BoundedBuffer<int, 23> buffer{};
  //	ASSERT_THROWS(buffer.front(), std::logic_error);
}

TEST(test_empty_const_bounded_buffer_throws_on_front) {
  //	BoundedBuffer<int, 23> const buffer{};
  //	ASSERT_THROWS(buffer.front(), std::logic_error);
}

TEST(test_empty_bounded_buffer_throws_on_back) {
  //	BoundedBuffer<int, 23> buffer{};
  //	ASSERT_THROWS(buffer.back(), std::logic_error);
}

TEST(test_empty_const_bounded_buffer_throws_on_back) {
  //	BoundedBuffer<int, 23> const buffer{};
  //	ASSERT_THROWS(buffer.back(), std::logic_error);
}

TEST(test_empty_bounded_buffer_throws_on_pop) {
  //	BoundedBuffer<int, 23> buffer{};
  //	ASSERT_THROWS(buffer.pop(), std::logic_error);
}

TEST(test_full_bounded_buffer_throws_on_push_const_lvalue) {
  //	BoundedBuffer<int, 0> buffer{};
  //	int const lvalue{23};
  //	ASSERT_THROWS(buffer.push(lvalue), std::logic_error);
}

TEST(test_full_bounded_buffer_throws_on_push_rvalue) {
  //	BoundedBuffer<int, 0> buffer{};
  //	ASSERT_THROWS(buffer.push(23), std::logic_error);
}

auto make_suite_bounded_buffer_default_behavior_suite() -> cute::suite {
  return cute::suite{
      "BoundedBuffer Default Behavior Suite",
      {
          test_int_buffer_of_capacity_thousand_is_empty,
          test_buffer_constructor_for_capacity_zero_is_empty,
          test_const_int_buffer_of_capacity_thousand_is_not_full,
          test_default_constructed_const_int_buffer_of_size_zero_is_full,
          test_int_buffer_of_capacity_thousand_has_size_zero,
          test_default_constructed_const_int_buffer_of_size_zero_has_size_zero,
          test_empty_bounded_buffer_throws_on_front,
          test_empty_const_bounded_buffer_throws_on_front,
          test_empty_bounded_buffer_throws_on_back,
          test_empty_const_bounded_buffer_throws_on_back,
          test_empty_bounded_buffer_throws_on_pop,
          test_full_bounded_buffer_throws_on_push_const_lvalue,
          test_full_bounded_buffer_throws_on_push_rvalue,
      }};
}
