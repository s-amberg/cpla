#include "BoundedBufferContentSuite.hpp"
#include "BoundedBuffer.hpp"

#include "NTimes.hpp"

#include <cute/cute.h>

#include <stdexcept>
#include <vector>

using namespace cpp_advanced::times_literal;

TEST(test_buffer_is_not_empty_after_push_rvalue) {
//   BoundedBuffer<int> buffer{5};
//   buffer.push(5);
//   ASSERTM("Buffer should not be empty after push", !buffer.empty());
}

TEST(test_buffer_is_not_empty_after_push_lvalue) {
//   BoundedBuffer<int> buffer{5};
//   int const lvalue{5};
//   buffer.push(lvalue);
//   ASSERTM("Buffer should not be empty after push", !buffer.empty());
}

TEST(test_buffer_is_empty_after_one_push_and_pop) {
//   BoundedBuffer<int> buffer{5};
//   buffer.push(5);
//   buffer.pop();
//   ASSERTM("Buffer should be empty after one push and pop", buffer.empty());
}

TEST(test_buffer_of_size_two_is_full_after_two_pushs) {
//   BoundedBuffer<int> buffer{2};
//   2_times([&]() { buffer.push(5); });
//   ASSERTM("Buffer of size two should be full after two pushs", buffer.full());
}

TEST(test_buffer_size_is_one_after_push) {
//   BoundedBuffer<int> buffer{2};
//   buffer.push(1);
//   ASSERT_EQUAL(1, buffer.size());
}

TEST(test_buffer_size_is_fifty_after_fifty_pushs) {
//   BoundedBuffer<int> buffer{75};
//   50_times([&]() { buffer.push(5); });
//   ASSERT_EQUAL(50, buffer.size());
}

TEST(test_buffer_front_gets_element_of_push) {
//   BoundedBuffer<int> buffer{5};
//   buffer.push(5);
//   ASSERT_EQUAL(5, buffer.front());
}

TEST(test_buffer_back_gets_element_of_push) {
//   BoundedBuffer<int> buffer{5};
//   buffer.push(5);
//   ASSERT_EQUAL(5, buffer.back());
}

TEST(test_buffer_front_gets_first_element_of_pushs) {
//   BoundedBuffer<int> buffer{5};
//   buffer.push(1);
//   buffer.push(2);
//   ASSERT_EQUAL(1, buffer.front());
}

TEST(test_buffer_back_gets_last_element_of_two_pushs) {
//   BoundedBuffer<int> buffer{5};
//   buffer.push(1);
//   buffer.push(2);
//   ASSERT_EQUAL(2, buffer.back());
}

TEST(test_buffer_front_throws_after_push_pop) {
//   BoundedBuffer<int> buffer{5};
//   buffer.push(5);
//   buffer.pop();
//   ASSERT_THROWS(buffer.front(), std::logic_error);
}

TEST(test_buffer_back_throws_after_push_pop) {
//   BoundedBuffer<int> buffer{5};
//   buffer.push(5);
//   buffer.pop();
//   ASSERT_THROWS(buffer.back(), std::logic_error);
}

TEST(test_const_buffer_front_gets_element_of_push) {
//   BoundedBuffer<int> buffer{5};
//   buffer.push(5);
//   auto const& constBuffer = buffer;
//   ASSERT_EQUAL(5, constBuffer.front());
}

TEST(test_const_buffer_back_gets_element_of_push) {
//   BoundedBuffer<int> buffer{5};
//   buffer.push(5);
//   auto const& constBuffer = buffer;
//   ASSERT_EQUAL(5, constBuffer.back());
}

TEST(test_const_buffer_front_gets_first_element_of_pushs) {
//   BoundedBuffer<int> buffer{5};
//   buffer.push(1);
//   buffer.push(2);
//   auto const& constBuffer = buffer;
//   ASSERT_EQUAL(1, constBuffer.front());
}

TEST(test_const_buffer_back_gets_last_element_of_two_pushs) {
//   BoundedBuffer<int> buffer{5};
//   buffer.push(1);
//   buffer.push(2);
//   auto const& constBuffer = buffer;
//   ASSERT_EQUAL(2, constBuffer.back());
}

TEST(test_const_buffer_front_throws_after_push_pop) {
//   BoundedBuffer<int> buffer{5};
//   buffer.push(5);
//   buffer.pop();
//   auto const& constBuffer = buffer;
//   ASSERT_THROWS(constBuffer.front(), std::logic_error);
}

TEST(test_const_buffer_back_throws_after_push_pop) {
//   BoundedBuffer<int> buffer{5};
//   buffer.push(5);
//   buffer.pop();
//   auto const& constBuffer = buffer;
//   ASSERT_THROWS(constBuffer.back(), std::logic_error);
}

TEST(test_buffer_fronts_in_sequence_of_push_pop) {
//   BoundedBuffer<int> buffer{5};
//   std::vector<int> frontValues{}, expectedValues{1, 1, 1, 2, 2, 3, 4, 4, 5};
//   buffer.push(1);
//   frontValues.push_back(buffer.front());
//   buffer.push(2);
//   frontValues.push_back(buffer.front());
//   buffer.push(3);
//   frontValues.push_back(buffer.front());
//   buffer.pop();
//   frontValues.push_back(buffer.front());
//   buffer.push(4);
//   frontValues.push_back(buffer.front());
//   buffer.pop();
//   frontValues.push_back(buffer.front());
//   buffer.pop();
//   frontValues.push_back(buffer.front());
//   buffer.push(5);
//   frontValues.push_back(buffer.front());
//   buffer.pop();
//   frontValues.push_back(buffer.front());
//   ASSERT_EQUAL(expectedValues, frontValues);
}

TEST(test_buffer_wrap_around_behavior_front) {
//   BoundedBuffer<int> buffer{3};
//   std::vector<int> frontValues{},
//       expectedValues{1, 1, 2, 2, 2, 3, 4, 4, 5, 5, 5, 6, 7};
//   buffer.push(1);
//   frontValues.push_back(buffer.front());
//   buffer.push(2);
//   frontValues.push_back(buffer.front());
//   buffer.pop();
//   frontValues.push_back(buffer.front());
//   buffer.push(3);
//   frontValues.push_back(buffer.front());
//   buffer.push(4);
//   frontValues.push_back(buffer.front());
//   buffer.pop();
//   frontValues.push_back(buffer.front());
//   buffer.pop();
//   frontValues.push_back(buffer.front());
//   buffer.push(5);
//   frontValues.push_back(buffer.front());
//   buffer.pop();
//   frontValues.push_back(buffer.front());
//   buffer.push(6);
//   frontValues.push_back(buffer.front());
//   buffer.push(7);
//   frontValues.push_back(buffer.front());
//   buffer.pop();
//   frontValues.push_back(buffer.front());
//   buffer.pop();
//   frontValues.push_back(buffer.front());
//   ASSERT_EQUAL(expectedValues, frontValues);
}

TEST(test_buffer_wrap_around_behavior_back) {
//   BoundedBuffer<int> buffer{3};
//   std::vector<int> backValues{},
//       expectedValues{1, 2, 2, 3, 4, 4, 4, 5, 5, 6, 7, 7, 7};
//   buffer.push(1);
//   backValues.push_back(buffer.back());
//   buffer.push(2);
//   backValues.push_back(buffer.back());
//   buffer.pop();
//   backValues.push_back(buffer.back());
//   buffer.push(3);
//   backValues.push_back(buffer.back());
//   buffer.push(4);
//   backValues.push_back(buffer.back());
//   buffer.pop();
//   backValues.push_back(buffer.back());
//   buffer.pop();
//   backValues.push_back(buffer.back());
//   buffer.push(5);
//   backValues.push_back(buffer.back());
//   buffer.pop();
//   backValues.push_back(buffer.back());
//   buffer.push(6);
//   backValues.push_back(buffer.back());
//   buffer.push(7);
//   backValues.push_back(buffer.back());
//   buffer.pop();
//   backValues.push_back(buffer.back());
//   buffer.pop();
//   backValues.push_back(buffer.back());
//   ASSERT_EQUAL(expectedValues, backValues);
}

TEST(test_buffer_after_swap_this_has_argument_content) {
//   std::vector<int> frontValues{}, expectedValues{1, 2, 3};
//   BoundedBuffer<int> buffer{5}, otherBuffer{5};
//   buffer.push(1);
//   buffer.push(2);
//   buffer.push(3);
//   otherBuffer.swap(buffer);
//   3_times([&]() {
//     frontValues.push_back(otherBuffer.front());
//     otherBuffer.pop();
//   });
//   ASSERT_EQUAL(expectedValues, frontValues);
}

TEST(test_buffer_after_swap_argument_has_this_content) {
//   std::vector<int> frontValues{}, expectedValues{1, 2, 3};
//   BoundedBuffer<int> buffer{5}, otherBuffer{5};
//   buffer.push(1);
//   buffer.push(2);
//   buffer.push(3);
//   buffer.swap(otherBuffer);
//   3_times([&]() {
//     frontValues.push_back(otherBuffer.front());
//     otherBuffer.pop();
//   });
//   ASSERT_EQUAL(expectedValues, frontValues);
}

auto make_suite_bounded_buffer_content_suite() -> cute::suite {
  return cute::suite{"BoundedBuffer Content Suite",
                     {
                         test_buffer_is_not_empty_after_push_rvalue,
                         test_buffer_is_not_empty_after_push_lvalue,
                         test_buffer_is_empty_after_one_push_and_pop,
                         test_buffer_of_size_two_is_full_after_two_pushs,
                         test_buffer_size_is_one_after_push,
                         test_buffer_size_is_fifty_after_fifty_pushs,
                         test_buffer_front_gets_element_of_push,
                         test_buffer_back_gets_element_of_push,
                         test_buffer_front_gets_first_element_of_pushs,
                         test_buffer_back_gets_last_element_of_two_pushs,
                         test_buffer_front_throws_after_push_pop,
                         test_buffer_back_throws_after_push_pop,
                         test_const_buffer_front_gets_element_of_push,
                         test_const_buffer_back_gets_element_of_push,
                         test_const_buffer_front_gets_first_element_of_pushs,
                         test_const_buffer_back_gets_last_element_of_two_pushs,
                         test_const_buffer_front_throws_after_push_pop,
                         test_const_buffer_back_throws_after_push_pop,
                         test_buffer_fronts_in_sequence_of_push_pop,
                         test_buffer_wrap_around_behavior_front,
                         test_buffer_wrap_around_behavior_back,
                         test_buffer_after_swap_this_has_argument_content,
                         test_buffer_after_swap_argument_has_this_content,
                     }};
}
