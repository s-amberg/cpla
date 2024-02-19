#include "BoundedBufferNDCElementTypeSuite.hpp"
#include "BoundedBuffer.hpp"

#include <cute/cute.h>
#include <stdexcept>
#include <string>


struct NonDefaultConstructible {
  NonDefaultConstructible(int) : value{1234} {}

  ~NonDefaultConstructible() {
    throwIfNotInitialized();
    nOfDtorCalls++;
  }

  NonDefaultConstructible(NonDefaultConstructible const& other)
      : value{other.value} {
    throwIfNotInitialized();
    nOfCopyConstructions++;
  }

  auto operator=(NonDefaultConstructible const& other)
      -> NonDefaultConstructible& {
    throwIfNotInitialized();
    other.throwIfNotInitialized();
    value = other.value;
    nOfCopyAssignments++;
    return *this;
  }

  auto operator=(NonDefaultConstructible&& other) -> NonDefaultConstructible& {
    throwIfNotInitialized();
    other.throwIfNotInitialized();
    std::swap(value, other.value);
    nOfMoveAssignments++;
    return *this;
  }

  NonDefaultConstructible(NonDefaultConstructible&& other) : value{1234} {
    other.throwIfNotInitialized();
    std::swap(value, other.value);
    nOfMoveConstructions++;
  }

  static unsigned nOfCopyConstructions;
  static unsigned nOfCopyAssignments;
  static unsigned nOfMoveConstructions;
  static unsigned nOfMoveAssignments;
  static unsigned nOfDtorCalls;

 private:
  void throwIfNotInitialized() const {
    if (value != 1234) {
      throw std::logic_error{"Operation on NDC with value: " +
                             std::to_string(value)};
    }
  }
  volatile unsigned value{};
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

TEST(test_new_buffer_of_nondefaultconstructible_invokes_no_destructors) {
//   resetCounters();
//   BoundedBuffer<NonDefaultConstructible> buffer{5};
//   ASSERT_EQUAL(0, NonDefaultConstructible::nOfDtorCalls);
}

TEST(test_element_in_buffer_is_destroyed_once) {
//   {
//     BoundedBuffer<NonDefaultConstructible> buffer{5};
//     buffer.push(NonDefaultConstructible{23});
//     resetCounters();
//   }
//   ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

TEST(test_element_in_moved_buffer_is_destroyed_once) {
//   {
//     BoundedBuffer<NonDefaultConstructible> buffer{5};
//     buffer.push(NonDefaultConstructible{23});
//     resetCounters();

//     BoundedBuffer<NonDefaultConstructible> moved{std::move(buffer)};
//   }

//   ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

TEST(test_every_element_in_copied_buffer_is_destroyed_once) {
//   {
//     BoundedBuffer<NonDefaultConstructible> buffer{5};
//     buffer.push(NonDefaultConstructible{23});
//     resetCounters();

//     BoundedBuffer<NonDefaultConstructible> copy{buffer};
//   }
//   ASSERT_EQUAL(2, NonDefaultConstructible::nOfDtorCalls);
}

TEST(test_pop_destroys_element) {
//   BoundedBuffer<NonDefaultConstructible> buffer{5};
//   buffer.push(NonDefaultConstructible{23});
//   resetCounters();

//   buffer.pop();

//   ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

TEST(test_lvalue_push_copies_element) {
//   resetCounters();
//   BoundedBuffer<NonDefaultConstructible> buffer{5};
//   NonDefaultConstructible element{23};

//   buffer.push(element);

//   ASSERT_EQUAL(1, NonDefaultConstructible::nOfCopyConstructions);
}

TEST(test_rvalue_push_moves_element) {
//   resetCounters();
//   BoundedBuffer<NonDefaultConstructible> buffer{5};
//   NonDefaultConstructible element{23};

//   buffer.push(std::move(element));

//   ASSERT_EQUAL(1, NonDefaultConstructible::nOfMoveConstructions);
}

TEST(test_lvalue_push_must_not_copy_assign) {
//   BoundedBuffer<NonDefaultConstructible> buffer{5};
//   NonDefaultConstructible element{23};

//   resetCounters();
//   buffer.push(element);

//   ASSERT_EQUAL(0, NonDefaultConstructible::nOfCopyAssignments);
}

TEST(test_rvalue_push_must_not_move_assign) {
//   BoundedBuffer<NonDefaultConstructible> buffer{5};
//   NonDefaultConstructible element{23};

//   resetCounters();
//   buffer.push(std::move(element));

//   ASSERT_EQUAL(0, NonDefaultConstructible::nOfMoveAssignments);
}

auto make_suite_bounded_buffer_non_default_constructible_element_type_suite()
    -> cute::suite {
  return cute::suite{
      "BoundedBuffer Non-Default Constructible Element Type Suite",
      {
          test_new_buffer_of_nondefaultconstructible_invokes_no_destructors,
          test_element_in_buffer_is_destroyed_once,
          test_element_in_moved_buffer_is_destroyed_once,
          test_every_element_in_copied_buffer_is_destroyed_once,
          test_pop_destroys_element,
          test_lvalue_push_copies_element,
          test_rvalue_push_moves_element,
          test_lvalue_push_must_not_copy_assign,
          test_rvalue_push_must_not_move_assign,
      }};
    }
