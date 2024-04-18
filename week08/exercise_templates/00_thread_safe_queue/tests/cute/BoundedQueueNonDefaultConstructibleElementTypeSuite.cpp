#include "BoundedQueueNonDefaultConstructibleElementTypeSuite.hpp"

#include <cute/cute.h>

// #include "BoundedQueue.hpp"

#include <stdexcept>
#include <utility>

struct NonDefaultConstructible {
  NonDefaultConstructible() = delete;

  explicit NonDefaultConstructible(int) : value{INITIALIZED} {}

  ~NonDefaultConstructible() {
    throwIfUninitialized();
    nOfDtorCalls++;
    value = 0;
  }

  NonDefaultConstructible(NonDefaultConstructible const &other) : value{other.value} {
    other.throwIfUninitialized();
    nOfCopyConstructions++;
  }

  auto operator=(NonDefaultConstructible const &other) -> NonDefaultConstructible & {
    throwIfUninitialized();
    other.throwIfUninitialized();
    nOfCopyAssignments++;
    return *this;
  }

  auto operator=(NonDefaultConstructible &&other) -> NonDefaultConstructible & {
    throwIfUninitialized();
    other.throwIfUninitialized();
    nOfMoveAssignments++;
    return *this;
  }

  NonDefaultConstructible(NonDefaultConstructible &&other) : value{INITIALIZED} {
    other.throwIfUninitialized();
    std::swap(value, other.value);
    nOfMoveConstructions++;
  }

  static unsigned nOfCopyConstructions;
  static unsigned nOfCopyAssignments;
  static unsigned nOfMoveConstructions;
  static unsigned nOfMoveAssignments;
  static unsigned nOfDtorCalls;

private:
  auto throwIfUninitialized() const -> void {
    if (value != 1234) {
      throw std::logic_error{"must not call operations on uninitialized NDC, with value: " + std::to_string(value)};
    }
  }

  volatile unsigned value;
  static const unsigned INITIALIZED = 1234;
};

unsigned NonDefaultConstructible::nOfCopyConstructions{0};
unsigned NonDefaultConstructible::nOfCopyAssignments{0};
unsigned NonDefaultConstructible::nOfMoveConstructions{0};
unsigned NonDefaultConstructible::nOfMoveAssignments{0};
unsigned NonDefaultConstructible::nOfDtorCalls{0};

void resetCounters() {
  NonDefaultConstructible::nOfCopyConstructions = 0;
  NonDefaultConstructible::nOfCopyAssignments = 0;
  NonDefaultConstructible::nOfMoveConstructions = 0;
  NonDefaultConstructible::nOfMoveAssignments = 0;
  NonDefaultConstructible::nOfDtorCalls = 0;
}

TEST(test_new_queue_of_nondefaultconstructible_invokes_no_destructors) {
  //   resetCounters();
  //   BoundedQueue<NonDefaultConstructible> queue{5};
  //   ASSERT_EQUAL(0, NonDefaultConstructible::nOfDtorCalls);
}

TEST(test_element_in_queue_is_destroyed_once) {
  //   {
  //     BoundedQueue<NonDefaultConstructible> queue{5};
  //     queue.push(NonDefaultConstructible{23});
  //     resetCounters();
  //   }
  //   ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

TEST(test_element_in_moved_queue_is_destroyed_once) {
  //   {
  //     BoundedQueue<NonDefaultConstructible> queue{5};
  //     queue.push(NonDefaultConstructible{23});
  //     resetCounters();

  //     BoundedQueue<NonDefaultConstructible> moved{std::move(queue)};
  //   }
  //   ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

TEST(test_every_element_in_copied_queue_is_destroyed_once) {
  //   {
  //     BoundedQueue<NonDefaultConstructible> queue{5};
  //     queue.push(NonDefaultConstructible{23});
  //     resetCounters();

  //     BoundedQueue<NonDefaultConstructible> copy{queue};
  //   }
  //   ASSERT_EQUAL(2, NonDefaultConstructible::nOfDtorCalls);
}

TEST(test_pop_destroys_element) {
  //   BoundedQueue<NonDefaultConstructible> queue{5};
  //   queue.push(NonDefaultConstructible{23});
  //   resetCounters();

  //   auto tmp = queue.pop();
  //   ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

TEST(test_lvalue_push_copies_element) {
  //   resetCounters();
  //   BoundedQueue<NonDefaultConstructible> queue{5};
  //   NonDefaultConstructible element{23};

  //   queue.push(element);

  //   ASSERT_EQUAL(1, NonDefaultConstructible::nOfCopyConstructions);
}

TEST(test_rvalue_push_moves_element) {
  //   resetCounters();
  //   BoundedQueue<NonDefaultConstructible> queue{5};
  //   NonDefaultConstructible element{23};

  //   queue.push(std::move(element));

  //   ASSERT_EQUAL(1, NonDefaultConstructible::nOfMoveConstructions);
}

TEST(test_lvalue_push_must_not_copy_assign) {
  //   BoundedQueue<NonDefaultConstructible> queue{5};
  //   NonDefaultConstructible element{23};

  //   resetCounters();
  //   queue.push(element);

  //   ASSERT_EQUAL(0, NonDefaultConstructible::nOfCopyAssignments);
}

TEST(test_rvalue_push_must_not_move_assign) {
  //   BoundedQueue<NonDefaultConstructible> queue{5};
  //   NonDefaultConstructible element{23};

  //   resetCounters();
  //   queue.push(std::move(element));

  //   ASSERT_EQUAL(0, NonDefaultConstructible::nOfMoveAssignments);
}

TEST(test_self_copy_assignment_unchanged_size) {
  //   BoundedQueue<NonDefaultConstructible> queue{5};
  //   queue.push(NonDefaultConstructible{23});

  //   resetCounters();
  //   queue = (queue);

  //   ASSERT_EQUAL(1, queue.size());
}

TEST(test_self_move_assignment_unchanged_size) {
  //   BoundedQueue<NonDefaultConstructible> queue{5};
  //   queue.push(NonDefaultConstructible{23});

  //   resetCounters();
  //   queue = std::move(queue);

  //   ASSERT_EQUAL(1, queue.size());
}

TEST(test_self_copy_assignment_no_copy_construction) {
  //   BoundedQueue<NonDefaultConstructible> queue{5};
  //   queue.push(NonDefaultConstructible{23});

  //   resetCounters();
  //   queue = (queue);

  //   ASSERT_EQUAL(0, NonDefaultConstructible::nOfCopyConstructions);
}

TEST(test_self_move_assignment_no_move_construction) {
  //   BoundedQueue<NonDefaultConstructible> queue{5};
  //   queue.push(NonDefaultConstructible{23});

  //   resetCounters();
  //   queue = std::move(queue);

  //   ASSERT_EQUAL(0, NonDefaultConstructible::nOfMoveConstructions);
}

TEST(test_copy_assignment_deletes_previous_elements) {
  //   BoundedQueue<NonDefaultConstructible> queue{5}, other{5};
  //   queue.push(NonDefaultConstructible{23});

  //   resetCounters();
  //   queue = other;

  //   ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

TEST(test_move_assignment_deletes_previous_elements_upon_destruction) {
  //   {
  //     BoundedQueue<NonDefaultConstructible> queue{5}, other{5};
  //     queue.push(NonDefaultConstructible{23});

  //     resetCounters();
  //     queue = std::move(other);
  //   }

  //   ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

auto make_suite_bounded_queue_non_default_constructible_element_type_suite() -> cute::suite {
  return cute::suite{"BoundedQueue Non Default Constructible Element Type Suite",
                     {
                         test_new_queue_of_nondefaultconstructible_invokes_no_destructors,
                         test_element_in_queue_is_destroyed_once,
                         test_element_in_moved_queue_is_destroyed_once,
                         test_every_element_in_copied_queue_is_destroyed_once,
                         test_pop_destroys_element,
                         test_lvalue_push_copies_element,
                         test_rvalue_push_moves_element,
                         test_lvalue_push_must_not_copy_assign,
                         test_rvalue_push_must_not_move_assign,
                         test_self_move_assignment_unchanged_size,
                         test_self_copy_assignment_unchanged_size,
                         test_self_copy_assignment_no_copy_construction,
                         test_self_move_assignment_no_move_construction,
                         test_copy_assignment_deletes_previous_elements,
                         test_move_assignment_deletes_previous_elements_upon_destruction,
                     }};
}
