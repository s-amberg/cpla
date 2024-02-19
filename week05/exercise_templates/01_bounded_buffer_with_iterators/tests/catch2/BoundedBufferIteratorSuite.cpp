#include "BoundedBuffer.hpp"

#include "NTimes.hpp"

#include <algorithm>
#include <cstddef>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>
#include <stdexcept>

using namespace cpp_advanced::times_literal;

TEST_CASE("test_begin_and_end_of_empty_buffer_are_equal", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{5};
  //  auto begin = buffer.begin();
  //  auto end = buffer.end();
  //  REQUIRE(begin == end);
}

TEST_CASE("test_begin_and_end_of_non_empty_buffer_are_inequal", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{5};
  //  buffer.push(23);
  //  auto begin = buffer.begin();
  //  auto end = buffer.end();
  //  REQUIRE(begin != end);
}

TEST_CASE("test_begin_and_end_of_full_buffer_are_inequal", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{5};
  //  5_times([&]() { buffer.push(23); });
  //  auto begin = buffer.begin();
  //  auto end = buffer.end();
  //  REQUIRE(begin != end);
}

//  auto createBufferWithFiveConsecutiveInts(int startValue) -> BoundedBuffer<int> {
//    BoundedBuffer<int> buffer{5};
//    auto i = startValue;
//    5_times([&/*, i = 0 */]() { buffer.push(i++); });
//    return buffer;
//  }

TEST_CASE("test_two_begins_of_same_buffer_are_equal", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};

  //  REQUIRE(buffer.begin() == buffer.begin());
}

TEST_CASE("test_two_ends_of_same_buffer_are_equal", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};

  //  REQUIRE(buffer.end() == buffer.end());
}

TEST_CASE("test_two_begins_of_same_const_buffer_are_equal", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(0)};

  //  REQUIRE(buffer.begin() == buffer.begin());
}

TEST_CASE("test_two_ends_of_same_const_buffer_are_equal", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(0)};

  //  REQUIRE(buffer.end() == buffer.end());
}

TEST_CASE("test_two_cbegins_of_same_const_buffer_are_equal", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(0)};

  //  REQUIRE(buffer.cbegin() == buffer.cbegin());
}

TEST_CASE("test_two_cends_of_same_const_buffer_are_equal", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(0)};

  //  REQUIRE(buffer.cend() == buffer.cend());
}

TEST_CASE("test_begin_points_to_the_correct_element", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};

  //  REQUIRE(15 == *buffer.begin());
}

TEST_CASE("test_prefix_incremented_begin_points_to_the_correct_element", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
  //  BoundedBuffer<int>::const_iterator iterator = buffer.begin();

  //  ++iterator;

  //  REQUIRE(16 == *iterator);
}

TEST_CASE("test_expression_of_prefix_incremented_begin_points_to_the_correct_element", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.begin();

  //  REQUIRE(16 == *(++iterator));
}

TEST_CASE("test_twice_prefix_incremented_begin_points_to_the_correct_element", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.begin();

  //  2_times([&]() { ++iterator; });

  //  REQUIRE(17 == *iterator);
}

TEST_CASE("test_postfix_incremented_begin_points_to_the_correct_element", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.begin();

  //  iterator++;

  //  REQUIRE(16 == *iterator);
}

TEST_CASE("test_expression_of_postfix_incremented_begin_points_to_the_correct_element", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.begin();

  //  REQUIRE(15 == *(iterator++));
}

TEST_CASE("test_iterator_prefix_incremented_to_the_end_equals_end", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.begin();

  //  5_times([&]() { ++iterator; });

  //  REQUIRE(buffer.end() == iterator);
}

TEST_CASE("test_iterator_incremented_wrap_around_leads_to_equal_end", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(15)};
  //  3_times([&]() { buffer.pop(); });
  //  buffer.push(20);
  //  buffer.push(21);
  //  auto iterator = buffer.begin();

  //  4_times([&]() { ++iterator; });

  //  REQUIRE(buffer.end() == iterator);
}

TEST_CASE("test_prefix_incrementing_end_iterator_throws", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{5};
  //  auto iterator = buffer.end();
  //  REQUIRE_THROWS_AS(++iterator, std::logic_error);
}

TEST_CASE("test_postfix_incrementing_end_iterator_throws", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{5};
  //  auto iterator = buffer.end();
  //  REQUIRE_THROWS_AS(iterator++, std::logic_error);
}

TEST_CASE("test_plus_expression_for_iterator", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.begin();

  //  REQUIRE(17 == *(iterator + 2));
}

TEST_CASE("test_plus_assign_expression_for_iterator", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.begin();

  //  iterator += 3;

  //  REQUIRE(18 == *iterator);
}

TEST_CASE("test_plus_beyond_end_throws", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.end();

  //  REQUIRE_THROWS_AS(iterator + 6, std::logic_error);
}

TEST_CASE("test_plus_assign_beyond_end_throws", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.end();

  //  REQUIRE_THROWS_AS(iterator += 6, std::logic_error);
}

TEST_CASE("test_minus_expression_for_iterator", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.end();

  //  REQUIRE(18 == *(iterator - 2));
}

TEST_CASE("test_minus_assign_expression_for_iterator", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.end();

  //  iterator -= 3;

  //  REQUIRE(17 == *iterator);
}

TEST_CASE("test_minus_beyond_begin_throws", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.end();

  //  REQUIRE_THROWS_AS(iterator - 6, std::logic_error);
}

TEST_CASE("test_minus_assign_beyond_begin_throws", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.end();

  //  REQUIRE_THROWS_AS(iterator -= 6, std::logic_error);
}

TEST_CASE("test_accessing_element_at_end_throws", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{5};
  //  auto iterator = buffer.end();
  //  REQUIRE_THROWS_AS(*iterator, std::logic_error);
}

TEST_CASE("test_postfix_decrementing_on_empty_buffer_begin_throws", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{5};
  //  auto iterator = buffer.begin();
  //  REQUIRE_THROWS_AS(iterator--, std::logic_error);
}

TEST_CASE("test_prefix_decrementing_on_empty_buffer_begin_throws", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{5};
  //  auto iterator = buffer.begin();
  //  REQUIRE_THROWS_AS(--iterator, std::logic_error);
}

TEST_CASE("test_postfix_decrementing_on_non_empty_buffer_begin_throws", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.begin();
  //  REQUIRE_THROWS_AS(iterator--, std::logic_error);
}

TEST_CASE("test_prefix_decrementing_on_non_empty_buffer_begin_throws", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.begin();
  //  REQUIRE_THROWS_AS(--iterator, std::logic_error);
}

TEST_CASE("test_postfix_decremented_end_points_to_last_element", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.end();

  //  iterator--;

  //  REQUIRE(19 == *iterator);
}

TEST_CASE("test_prefix_decremented_end_points_to_last_element", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(15)};
  //  auto iterator = buffer.end();

  //  --iterator;

  //  REQUIRE(19 == *iterator);
}

TEST_CASE("test_begin_end_ranges_of_the_same_buffer_are_equal", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(0)};
  //  REQUIRE(std::equal(buffer.begin(), buffer.end(), buffer.begin()));
}

TEST_CASE("test_begin_end_ranges_of_buffers_with_the_same_elements_are_equal", "[Iterator Suite]") {
  //  BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(0)};
  //  BoundedBuffer<int> const buffer2{createBufferWithFiveConsecutiveInts(0)};
  //  REQUIRE(std::equal(buffer.begin(), buffer.end(), buffer2.begin()));
}

TEST_CASE("test_difference_on_different_buffers_throws", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{5}, buffer2{5};
  //  REQUIRE_THROWS_AS(buffer.begin() - buffer2.begin(), std::logic_error);
}

TEST_CASE("test_difference_between_begin_and_end_on_empty_buffer", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{5};
  //  std::ptrdiff_t distance = buffer.end() - buffer.begin();
  //  REQUIRE(0 == distance);
}

TEST_CASE("test_difference_between_begin_and_end_on_buffer_with_some_elements", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{5};
  //  3_times([&]() { buffer.push(27); });
  //  std::ptrdiff_t distance = buffer.end() - buffer.begin();
  //  REQUIRE(3 == distance);
}

TEST_CASE("test_difference_between_begin_and_end_on_buffer_with_some_elements_wrapped_around", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(15)};
  //  3_times([&]() { buffer.pop(); });
  //  buffer.push(20);
  //  buffer.push(21);

  //  std::ptrdiff_t distance = buffer.end() - buffer.begin();

  //  REQUIRE(4 == distance);
}

TEST_CASE("test_difference_between_arbitrary_iterators_on_buffer_with_some_elements_wrapped_around", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(15)};
  //  3_times([&]() { buffer.pop(); });
  //  buffer.push(20);
  //  buffer.push(21);
  //  auto begin = buffer.begin();
  //  auto end = buffer.end();

  //  begin++;
  //  end--;
  //  std::ptrdiff_t distance = end - begin;

  //  REQUIRE(2 == distance);
}

TEST_CASE("test_difference_between_begin_and_end_on_full_buffer", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
  //  std::ptrdiff_t distance = buffer.end() - buffer.begin();
  //  REQUIRE(5 == distance);
}

TEST_CASE("test_begin_end_ranges_of_buffers_with_the_same_elements_but_not_at_the_same_location_are_equal", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{5};
  //  3_times([&]() {
  //    buffer.push(23);
  //    buffer.pop();
  //  });
  //  auto i = 0;
  //  5_times([&]() { buffer.push(i++); });
  //  BoundedBuffer<int> const buffer2{createBufferWithFiveConsecutiveInts(0)};
  //  REQUIRE_THAT(buffer, Catch::Matchers::RangeEquals(buffer2));
}

TEST_CASE("test_begin_is_smaller_than_end_for_non_empty_buffers", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
  //  REQUIRE(buffer.begin() < buffer.end());
}

TEST_CASE("test_begin_is_greater_than_end_for_non_empty_buffers", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
  //  REQUIRE(buffer.end() > buffer.begin());
}

TEST_CASE("test_arbitrary_iterators_compare_less_than_for_non_empty_buffers", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
  //  auto lower = buffer.begin();
  //  auto greater = buffer.end();

  //  lower++;
  //  greater--;

  //  REQUIRE(lower < greater);
}

TEST_CASE("test_arbitrary_iterators_compare_greater_than_for_non_empty_buffers", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
  //  auto lower = buffer.begin();
  //  auto greater = buffer.end();

  //  lower++;
  //  greater--;

  //  REQUIRE(greater > lower);
}

TEST_CASE("test_relative_comparison_of_iterators_to_different_buffers_throws", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{5}, buffer2{5};

  //  REQUIRE_THROWS_AS(buffer.begin() < buffer2.begin(), std::logic_error);
}

TEST_CASE("test_non_const_begin_iterator_overwrites_element", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
  //  *buffer.begin() = 23;
  //  REQUIRE(23 == buffer.front());
}

TEST_CASE("test_non_const_end_iterator_overwrites_element", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
  //  BoundedBuffer<int>::iterator iterator = buffer.end();
  //  *(--iterator) = 23;
  //  REQUIRE(23 == buffer.back());
}

TEST_CASE("test_index_operator", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
  //  REQUIRE(2 == buffer.begin()[2]);
}

TEST_CASE("test_index_end_minus_one_operator", "[Iterator Suite]") {
  //  BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
  //  REQUIRE(buffer.back() == buffer.end()[-1]);
}

struct TypeWithMember {
  int value;
};

TEST_CASE("test_arrow_operator", "[Iterator Suite]") {
  //  BoundedBuffer<TypeWithMember> buffer{5};

  //  buffer.push(TypeWithMember{23});

  //  REQUIRE(23 == buffer.begin()->value);
}
