#include "BoundedBufferMakeBufferSuite.hpp"
#include "BoundedBuffer.hpp"
#include "MemoryOperationCounter.hpp"

#include <cute/cute.h>

//--- a) ---

TEST(test_make_bounded_buffer_from_rvalue_argument_contains_one_element) {
//   BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{});
//   ASSERT_EQUAL(1, buffer.size());
}

TEST(test_make_bounded_buffer_from_rvalue_argument_object_moved) {
//   MemoryOperationCounter expected{1, 0, true};
//   BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{});
//   ASSERT_EQUAL(expected, buffer.front());
}

TEST(test_bounded_buffer_constructed_with_lvalue_argument_object_copied) {
//   MemoryOperationCounter expected{0, 1, true};
//   MemoryOperationCounter insertee{};
//   BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(insertee);
//   ASSERT_EQUAL(expected, buffer.front());
}

TEST(test_bounded_buffer_constructed_with_const_lvalue_argument_object_copied) {
//   MemoryOperationCounter expected{0, 1, true};
//   MemoryOperationCounter const insertee{};
//   BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(insertee);
//   ASSERT_EQUAL(expected, buffer.front());
}


//--- b) ---


TEST(test_make_bounded_buffer_from_two_rvalue_arguments_contains_two_elements) {
//  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, MemoryOperationCounter{});
//  ASSERT_EQUAL(2, buffer.size());
}

TEST(test_make_bounded_buffer_from_two_lvalue_arguments_contains_two_elements) {
//  MemoryOperationCounter element1{}, element2{};
//  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(element1, element2);
//  ASSERT_EQUAL(2, buffer.size());
}

TEST(test_make_bounded_buffer_from_too_many_elements_throws) {
//  ASSERT_THROWS((BoundedBuffer<int, 1>::make_buffer(1, 2)), std::invalid_argument);
}

TEST(test_make_bounded_buffer_from_two_rvalue_arguments_first_element_moved) {
//  MemoryOperationCounter expected{1, 0, true};
//  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, MemoryOperationCounter{});
//
//  ASSERT_EQUAL(expected, buffer.front());
}

TEST(test_make_bounded_buffer_from_two_rvalue_arguments_second_element_moved) {
//  MemoryOperationCounter expected{1, 0, true};
//  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, MemoryOperationCounter{});
//  ASSERT_EQUAL(expected, buffer.back());
}

TEST(test_make_bounded_buffer_from_two_rvalue_arguments_first_element_copied) {
//  MemoryOperationCounter expected{0, 1, true};
//  MemoryOperationCounter lvalue{};
//  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(lvalue, MemoryOperationCounter{});
//  ASSERT_EQUAL(expected, buffer.front());
}

TEST(test_make_bounded_buffer_from_two_mixed_arguments_second_element_moved) {
//  MemoryOperationCounter expected{1, 0, true};
//  MemoryOperationCounter lvalue{};
//  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(lvalue, MemoryOperationCounter{});
//  ASSERT_EQUAL(expected, buffer.back());
}

TEST(test_make_bounded_buffer_from_two_rvalue_arguments_second_element_copied) {
//  MemoryOperationCounter expected{0, 1, true};
//  MemoryOperationCounter lvalue{};
//  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, lvalue);
//  ASSERT_EQUAL(expected, buffer.back());
}

TEST(test_make_bounded_buffer_from_two_mixed_arguments_first_element_moved) {
//  MemoryOperationCounter expected{1, 0, true};
//  MemoryOperationCounter lvalue{};
//  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, lvalue);
//  ASSERT_EQUAL(expected, buffer.front());
}


auto make_suite_bounded_buffer_make_buffer_suite() -> cute::suite {
	return cute::suite{"BoundedBuffer Make Buffer Suite", {

	//--- a) ---
	test_make_bounded_buffer_from_rvalue_argument_contains_one_element,
	test_make_bounded_buffer_from_rvalue_argument_object_moved,
	test_bounded_buffer_constructed_with_lvalue_argument_object_copied,
	test_bounded_buffer_constructed_with_const_lvalue_argument_object_copied,

	//--- b) ---
	test_make_bounded_buffer_from_two_rvalue_arguments_contains_two_elements,
	test_make_bounded_buffer_from_two_lvalue_arguments_contains_two_elements,
	test_make_bounded_buffer_from_too_many_elements_throws,
	test_make_bounded_buffer_from_two_rvalue_arguments_first_element_moved,
	test_make_bounded_buffer_from_two_rvalue_arguments_second_element_moved,
	test_make_bounded_buffer_from_two_rvalue_arguments_first_element_copied,
	test_make_bounded_buffer_from_two_mixed_arguments_second_element_moved,
	test_make_bounded_buffer_from_two_rvalue_arguments_second_element_copied,
	test_make_bounded_buffer_from_two_mixed_arguments_first_element_moved,
	}
	};	
}
