#include "BoundedBufferSemanticSuite.hpp"
#include "BoundedBuffer.hpp"

#include "MemoryOperationCounter.hpp"

#include <cute/cute.h>

#include <utility>

TEST(test_buffer_push_copies_element) {
//   BoundedBuffer<MemoryOperationCounter> buffer{1};
//   MemoryOperationCounter counter{}, expected{0, 1, true};
//   buffer.push(counter);
//   ASSERT_EQUAL(expected, buffer.front());
}

TEST(test_buffer_push_moves_element) {
//   BoundedBuffer<MemoryOperationCounter> buffer{1};
//   MemoryOperationCounter counter{}, expected{1, 0, true};
//   buffer.push(std::move(counter));
//   ASSERT_EQUAL(expected, buffer.front());
}

TEST(test_element_in_buffer_is_copied_along_copy_constructor) {
//   BoundedBuffer<MemoryOperationCounter> buffer{1};
//   MemoryOperationCounter counter{}, expected{0, 2, true};
//   buffer.push(counter);
//   BoundedBuffer<MemoryOperationCounter> const& constBuffer = buffer;
//   BoundedBuffer<MemoryOperationCounter> bufferCopied{constBuffer};
//   ASSERT_EQUAL(expected, bufferCopied.front());
}

TEST(test_element_in_buffer_is_copied_along_assignment_operator) {
//   BoundedBuffer<MemoryOperationCounter> buffer{1}, bufferCopied{1};
//   MemoryOperationCounter counter{}, expected{0, 2, true};
//   buffer.push(counter);
//   BoundedBuffer<MemoryOperationCounter> const& constBuffer = buffer;
//   bufferCopied = constBuffer;
//   ASSERT_EQUAL(expected, bufferCopied.front());
}

TEST(test_element_in_buffer_is_moved_along_move_constructor) {
//   BoundedBuffer<MemoryOperationCounter> buffer{1};
//   MemoryOperationCounter counter{}, expected{1, 0, true};
//   buffer.push(std::move(counter));
//   BoundedBuffer<MemoryOperationCounter> bufferMoved{std::move(buffer)};
//   ASSERT_EQUAL(expected, bufferMoved.front());
}

TEST(test_element_in_buffer_is_moved_along_assignment_operator) {
//   BoundedBuffer<MemoryOperationCounter> buffer{1}, bufferMoved{1};
//   MemoryOperationCounter counter{}, expected{1, 0, true};
//   buffer.push(std::move(counter));
//   bufferMoved = std::move(buffer);
//   ASSERT_EQUAL(expected, bufferMoved.front());
}

TEST(test_element_in_buffer_is_copied_along_assignment_operator_multiple_copies) {
//   BoundedBuffer<MemoryOperationCounter> buffer{1}, intermediate1{1},
//       intermediate2{1}, bufferCopied{1};
//   MemoryOperationCounter counter{}, expected{0, 4, true};
//   buffer.push(counter);
//   bufferCopied = intermediate2 = intermediate1 = buffer;
//   ASSERT_EQUAL(expected, bufferCopied.front());
}

TEST(test_element_in_buffer_is_moved_along_assignment_operator_multiple_moves) {
//   BoundedBuffer<MemoryOperationCounter> buffer{1}, intermediate1{1},
//       intermediate2{1}, bufferMoved{1};
//   MemoryOperationCounter counter{}, expected{1, 0, true};
//   buffer.push(std::move(counter));
//   bufferMoved =
//       std::move(intermediate1 = std::move(intermediate2 = std::move(buffer)));
//   ASSERT_EQUAL(expected, bufferMoved.front());
}

TEST(test_element_buffer_copy_is_returned_from_assignment) {
//   BoundedBuffer<MemoryOperationCounter> buffer{1}, bufferCopied{1};
//   MemoryOperationCounter counter{}, expected{0, 2, true};
//   buffer.push(counter);
//   BoundedBuffer<MemoryOperationCounter> const& constBuffer = buffer;
//   ASSERT_EQUAL(expected, (bufferCopied = constBuffer).front());
}

TEST(test_element_buffer_moved_is_returned_from_assignment) {
//   BoundedBuffer<MemoryOperationCounter> buffer{1}, bufferMoved{1};
//   MemoryOperationCounter counter{}, expected{1, 0, true};
//   buffer.push(std::move(counter));
//   ASSERT_EQUAL(expected, (bufferMoved = std::move(buffer)).front());
}

TEST(test_capacity_is_copied_in_ctor) {
//   // given
//   BoundedBuffer<MemoryOperationCounter> buffer{4};
//   buffer.push(MemoryOperationCounter{});
//   buffer.push(MemoryOperationCounter{});

//   // when
//   BoundedBuffer<MemoryOperationCounter> copy{buffer};
//   copy.push(MemoryOperationCounter{});
//   copy.push(MemoryOperationCounter{});

//   // then
//   ASSERT(copy.full());
}

TEST(test_capacity_is_copied_in_assignment) {
//   // given
//   BoundedBuffer<MemoryOperationCounter> buffer{4}, copy{1};
//   buffer.push(MemoryOperationCounter{});
//   buffer.push(MemoryOperationCounter{});

//   // when
//   copy = buffer;
//   copy.push(MemoryOperationCounter{});
//   copy.push(MemoryOperationCounter{});

//   // then
//   ASSERT(copy.full());
}

TEST(test_capacity_is_moved_in_ctor) {
//   // given
//   BoundedBuffer<MemoryOperationCounter> buffer{4};
//   buffer.push(MemoryOperationCounter{});
//   buffer.push(MemoryOperationCounter{});

//   // when
//   BoundedBuffer<MemoryOperationCounter> copy{std::move(buffer)};
//   copy.push(MemoryOperationCounter{});
//   copy.push(MemoryOperationCounter{});

//   // then
//   ASSERT(copy.full());
}

TEST(test_capacity_is_moved_in_assignment) {
//   // given
//   BoundedBuffer<MemoryOperationCounter> buffer{4}, copy{1};
//   buffer.push(MemoryOperationCounter{});
//   buffer.push(MemoryOperationCounter{});

//   // when
//   copy = std::move(buffer);
//   copy.push(MemoryOperationCounter{});
//   copy.push(MemoryOperationCounter{});

//   // then
//   ASSERT(copy.full());
}

auto make_suite_bounded_buffer_semantic_suite() -> cute::suite {
  return cute::suite{
      "BoundedBuffer Semantic Suite",
      {
          test_buffer_push_moves_element,
          test_buffer_push_copies_element,
          test_element_in_buffer_is_copied_along_copy_constructor,
          test_element_in_buffer_is_copied_along_assignment_operator,
          test_element_in_buffer_is_moved_along_move_constructor,
          test_element_in_buffer_is_moved_along_assignment_operator,
          test_element_in_buffer_is_copied_along_assignment_operator_multiple_copies,
          test_element_in_buffer_is_moved_along_assignment_operator_multiple_moves,
          test_element_buffer_copy_is_returned_from_assignment,
          test_element_buffer_moved_is_returned_from_assignment,
          test_capacity_is_copied_in_ctor,
          test_capacity_is_copied_in_assignment,
          test_capacity_is_moved_in_ctor,
          test_capacity_is_moved_in_assignment,
      }};
}
