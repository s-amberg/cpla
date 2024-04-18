#include "BoundedQueueSemanticSuite.hpp"

#include <cute/cute.h>

// #include "BoundedQueue.hpp"
#include "MemoryOperationCounter.hpp"

#include <utility>

TEST(test_queue_push_copies_element) {
  //   BoundedQueue<MemoryOperationCounter> queue{1};
  //   MemoryOperationCounter counter{}, expected{1, 1, true};
  //   queue.push(counter);
  //   ASSERT_EQUAL(expected, queue.pop());
}

TEST(test_queue_push_moves_element) {
  //   BoundedQueue<MemoryOperationCounter> queue{1};
  //   MemoryOperationCounter counter{}, expected{2, 0, true};
  //   queue.push(std::move(counter));
  //   ASSERT_EQUAL(expected, queue.pop());
}

TEST(test_element_in_queue_is_copied_along_copy_constructor) {
  //   BoundedQueue<MemoryOperationCounter> queue{1};
  //   MemoryOperationCounter counter{}, expected{1, 2, true};
  //   queue.push(counter);
  //   BoundedQueue<MemoryOperationCounter> const &constQueue = queue;
  //   BoundedQueue<MemoryOperationCounter> queueCopied{constQueue};
  //   ASSERT_EQUAL(expected, queueCopied.pop());
}

TEST(test_element_in_queue_is_copied_along_assignment_operator) {
  //   BoundedQueue<MemoryOperationCounter> queue{1}, queueCopied{1};
  //   MemoryOperationCounter counter{}, expected{1, 2, true};
  //   queue.push(counter);
  //   BoundedQueue<MemoryOperationCounter> const &constQueue = queue;
  //   queueCopied = constQueue;
  //   ASSERT_EQUAL(expected, queueCopied.pop());
}

TEST(test_element_in_queue_is_moved_along_move_constructor) {
  //   BoundedQueue<MemoryOperationCounter> queue{1};
  //   MemoryOperationCounter counter{}, expected{2, 0, true};
  //   queue.push(std::move(counter));
  //   BoundedQueue<MemoryOperationCounter> queueMoved{std::move(queue)};
  //   ASSERT_EQUAL(expected, queueMoved.pop());
}

TEST(test_element_in_queue_is_moved_along_assignment_operator) {
  //   BoundedQueue<MemoryOperationCounter> queue{1}, queueMoved{1};
  //   MemoryOperationCounter counter{}, expected{2, 0, true};
  //   queue.push(std::move(counter));
  //   queueMoved = std::move(queue);
  //   ASSERT_EQUAL(expected, queueMoved.pop());
}

TEST(test_element_in_queue_is_copied_along_assignment_operator_multiple_copies) {
  //   BoundedQueue<MemoryOperationCounter> queue{1}, intermediate1{1}, intermediate2{1}, queueCopied{1};
  //   MemoryOperationCounter counter{}, expected{1, 4, true};
  //   queue.push(counter);
  //   queueCopied = intermediate2 = intermediate1 = queue;
  //   ASSERT_EQUAL(expected, queueCopied.pop());
}

TEST(test_element_in_queue_is_moved_along_assignment_operator_multiple_moves) {
  //   BoundedQueue<MemoryOperationCounter> queue{1}, intermediate1{1}, intermediate2{1}, queueMoved{1};
  //   MemoryOperationCounter counter{}, expected{2, 0, true};
  //   queue.push(std::move(counter));
  //   queueMoved = std::move(intermediate1 = std::move(intermediate2 = std::move(queue)));
  //   ASSERT_EQUAL(expected, queueMoved.pop());
}

TEST(test_element_queue_copy_is_returned_from_assignment) {
  //   BoundedQueue<MemoryOperationCounter> queue{1}, queueCopied{1};
  //   MemoryOperationCounter counter{}, expected{1, 2, true};
  //   queue.push(counter);
  //   BoundedQueue<MemoryOperationCounter> const &constQueue = queue;
  //   ASSERT_EQUAL(expected, (queueCopied = constQueue).pop());
}

TEST(test_element_queue_moved_is_returned_from_assignment) {
  //   BoundedQueue<MemoryOperationCounter> queue{1}, queueMoved{1};
  //   MemoryOperationCounter counter{}, expected{2, 0, true};
  //   queue.push(std::move(counter));
  //   ASSERT_EQUAL(expected, (queueMoved = std::move(queue)).pop());
}

TEST(test_capacity_is_copied_in_ctor) {
  //   // given
  //   BoundedQueue<MemoryOperationCounter> queue{4};
  //   queue.push(MemoryOperationCounter{});
  //   queue.push(MemoryOperationCounter{});

  //   // when
  //   BoundedQueue<MemoryOperationCounter> copy{queue};
  //   copy.push(MemoryOperationCounter{});
  //   copy.push(MemoryOperationCounter{});

  //   // then
  //   ASSERT(copy.full());
}

TEST(test_capacity_is_copied_in_assignment) {
  //   // given
  //   BoundedQueue<MemoryOperationCounter> queue{4}, copy{1};
  //   queue.push(MemoryOperationCounter{});
  //   queue.push(MemoryOperationCounter{});

  //   // when
  //   copy = queue;
  //   copy.push(MemoryOperationCounter{});
  //   copy.push(MemoryOperationCounter{});

  //   // then
  //   ASSERT(copy.full());
}

TEST(test_capacity_is_moved_in_ctor) {
  //   // given
  //   BoundedQueue<MemoryOperationCounter> queue{4};
  //   queue.push(MemoryOperationCounter{});
  //   queue.push(MemoryOperationCounter{});

  //   // when
  //   BoundedQueue<MemoryOperationCounter> copy{std::move(queue)};
  //   copy.push(MemoryOperationCounter{});
  //   copy.push(MemoryOperationCounter{});

  //   // then
  //   ASSERT(copy.full());
}

TEST(test_capacity_is_moved_in_assignment) {
  //   // given
  //   BoundedQueue<MemoryOperationCounter> queue{4}, copy{1};
  //   queue.push(MemoryOperationCounter{});
  //   queue.push(MemoryOperationCounter{});

  //   // when
  //   copy = std::move(queue);
  //   copy.push(MemoryOperationCounter{});
  //   copy.push(MemoryOperationCounter{});

  //   // then
  //   ASSERT(copy.full());
}

auto make_suite_bounded_queue_semantic_suite() -> cute::suite {
  return cute::suite{"BoundedQueue Semantic Suite",
                     {
                         test_queue_push_moves_element,
                         test_queue_push_copies_element,
                         test_element_in_queue_is_copied_along_copy_constructor,
                         test_element_in_queue_is_copied_along_assignment_operator,
                         test_element_in_queue_is_moved_along_move_constructor,
                         test_element_in_queue_is_moved_along_assignment_operator,
                         test_element_in_queue_is_copied_along_assignment_operator_multiple_copies,
                         test_element_in_queue_is_moved_along_assignment_operator_multiple_moves,
                         test_element_queue_copy_is_returned_from_assignment,
                         test_element_queue_moved_is_returned_from_assignment,
                         test_capacity_is_copied_in_ctor,
                         test_capacity_is_copied_in_assignment,
                         test_capacity_is_moved_in_ctor,
                         test_capacity_is_moved_in_assignment,
                     }};
}
