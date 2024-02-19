#include "FibonacciIterator.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

TEST(test_default_constructed_iterator_returns_zero) {
  FibonacciIterator const fibItr{};

  ASSERT_EQUAL(0, *fibItr);
}

TEST(test_fibonacci_iterator_for_first_element_is_one) {
  FibonacciIterator const fibItr{1};

  ASSERT_EQUAL(1, *fibItr);
}

TEST(test_fibonacci_iterator_for_second_element_is_one) {
  FibonacciIterator const fibItr{2};

  ASSERT_EQUAL(1, *fibItr);
}

TEST(test_fibonacci_iterator_for_third_element_is_two) {
  FibonacciIterator const fibItr{3};

  ASSERT_EQUAL(2, *fibItr);
}

TEST(test_fibonacci_iterator_for_fourth_element_is_three) {
  FibonacciIterator const fibItr{4};

  ASSERT_EQUAL(3, *fibItr);
}

TEST(test_fibonacci_iterator_for_fifth_element_is_five) {
  FibonacciIterator const fibItr{5};

  ASSERT_EQUAL(5, *fibItr);
}

TEST(test_fibonacci_iterator_for_sixth_element_is_eight) {
  FibonacciIterator const fibItr{6};

  ASSERT_EQUAL(8, *fibItr);
}

TEST(test_fibonacci_iterator_for_seventh_element_is_thirteen) {
  FibonacciIterator const fibItr{7};

  ASSERT_EQUAL(13, *fibItr);
}

TEST(test_fibonacci_iterator_for_eighth_element_is_twentyone) {
  FibonacciIterator const fibItr{8};

  ASSERT_EQUAL(21, *fibItr);
}

TEST(test_fibonacci_iterator_for_ninth_element_is_thirtyfour) {
  FibonacciIterator const fibItr{9};

  ASSERT_EQUAL(34, *fibItr);
}

TEST(test_fibonacci_iterator_for_tenth_element_is_fiftyfive) {
  FibonacciIterator const fibItr{10};

  ASSERT_EQUAL(55, *fibItr);
}

TEST(test_fibonacci_iterator_equal_to_itself) {
  FibonacciIterator const fibItr{};

  ASSERT_EQUAL(fibItr, fibItr);
}

TEST(test_fibonacci_iterator_equal_to_other_fibonacci_iterator_with_same_state) {
  FibonacciIterator const fibItr{10}, otherFibItr{10};

  ASSERT_EQUAL(fibItr, otherFibItr);
}

TEST(test_fibonacci_iterator_not_equal_to_other_fibonacci_iterator_with_another_state) {
  FibonacciIterator const fibItr{5}, otherFibItr{10};

  ASSERT_NOT_EQUAL_TO(fibItr, otherFibItr);
}

TEST(test_prefix_incrementing_default_fibonacci_iterator_increments_this_fibonacci_iterator) {
  FibonacciIterator const expectedItr{1};
  FibonacciIterator otherFibItr{};

  ++otherFibItr;

  ASSERT_EQUAL(expectedItr, otherFibItr);
}

TEST(test_prefix_incrementing_default_fibonacci_iterator_returns_changed_fibonacci_iterator) {
  FibonacciIterator fibItr{};

  FibonacciIterator& changed{++fibItr};

  ASSERT_EQUAL(&changed, &fibItr);
}

TEST(test_postfix_incrementing_default_fibonacci_iterator_increments_this_fibonacci_iterator) {
  FibonacciIterator const expectedItr{1};
  FibonacciIterator otherFibItr{};

  otherFibItr++;

  ASSERT_EQUAL(expectedItr, otherFibItr);
}

TEST(test_postfix_incrementing_default_fibonacci_iterator_returns_previous_value_fibonacci_iterator) {
  FibonacciIterator const expectedItr{};
  FibonacciIterator otherFibItr{};

  FibonacciIterator const unincremented{otherFibItr++};

  ASSERT_EQUAL(expectedItr, unincremented);
}

TEST(test_postfix_incrementing_default_fibonacci_iterator_returns_new_fibonacci_iterator) {
  FibonacciIterator fibItr{};

  FibonacciIterator const& changed{fibItr++};

  ASSERT_NOT_EQUAL_TO(&changed, &fibItr);
}

auto main(int argc, char const* argv[]) -> int {
  auto suite = cute::suite{
      "FibonacciIterator Tests",
      {
          test_default_constructed_iterator_returns_zero,
          test_fibonacci_iterator_for_first_element_is_one,
          test_fibonacci_iterator_for_second_element_is_one,
          test_fibonacci_iterator_for_third_element_is_two,
          test_fibonacci_iterator_for_fourth_element_is_three,
          test_fibonacci_iterator_for_fifth_element_is_five,
          test_fibonacci_iterator_for_sixth_element_is_eight,
          test_fibonacci_iterator_for_seventh_element_is_thirteen,
          test_fibonacci_iterator_for_eighth_element_is_twentyone,
          test_fibonacci_iterator_for_ninth_element_is_thirtyfour,
          test_fibonacci_iterator_for_tenth_element_is_fiftyfive,
          test_fibonacci_iterator_equal_to_itself,
          test_fibonacci_iterator_equal_to_other_fibonacci_iterator_with_same_state,
          test_fibonacci_iterator_not_equal_to_other_fibonacci_iterator_with_another_state,
          test_prefix_incrementing_default_fibonacci_iterator_increments_this_fibonacci_iterator,
          test_prefix_incrementing_default_fibonacci_iterator_returns_changed_fibonacci_iterator,
          test_postfix_incrementing_default_fibonacci_iterator_increments_this_fibonacci_iterator,
          test_postfix_incrementing_default_fibonacci_iterator_returns_previous_value_fibonacci_iterator,
          test_postfix_incrementing_default_fibonacci_iterator_returns_new_fibonacci_iterator,
      }};

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}
