// #include "BoundedQueue.hpp"

#include <catch2/catch_test_macros.hpp>

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

auto resetCounters() -> void {
  NonDefaultConstructible::nOfCopyConstructions = 0;
  NonDefaultConstructible::nOfCopyAssignments = 0;
  NonDefaultConstructible::nOfMoveConstructions = 0;
  NonDefaultConstructible::nOfMoveAssignments = 0;
  NonDefaultConstructible::nOfDtorCalls = 0;
}

TEST_CASE("New queue of non-default constructible invokes no destructors", "[Non-Default-Constructible Element Suite]") {
  // resetCounters();
  // BoundedQueue<NonDefaultConstructible> queue{5};
  // REQUIRE(NonDefaultConstructible::nOfDtorCalls == 0);
}

TEST_CASE("Element in queue is destroyed once", "[Non-Default-Constructible Element Suite]") {
  // {
  //   BoundedQueue<NonDefaultConstructible> queue{5};
  //   queue.push(NonDefaultConstructible{23});
  //   resetCounters();
  // }
  // REQUIRE(NonDefaultConstructible::nOfDtorCalls == 1);
}

TEST_CASE("Element in moved queue buffer is destroyed once", "[Non-Default-Constructible Element Suite]") {
  // {
  //   BoundedQueue<NonDefaultConstructible> queue{5};
  //   queue.push(NonDefaultConstructible{23});
  //   resetCounters();

  //   BoundedQueue<NonDefaultConstructible> moved{std::move(queue)};
  // }

  // REQUIRE(NonDefaultConstructible::nOfDtorCalls == 1);
}

TEST_CASE("Every element in copied queue is destroyed once", "[Non-Default-Constructible Element Suite]") {
  // {
  //   BoundedQueue<NonDefaultConstructible> queue{5};
  //   queue.push(NonDefaultConstructible{23});
  //   resetCounters();

  //   BoundedQueue<NonDefaultConstructible> copy{queue};
  // }
  // REQUIRE(NonDefaultConstructible::nOfDtorCalls == 2);
}

TEST_CASE("Pop destroys element", "[Non-Default-Constructible Element Suite]") {
  // BoundedQueue<NonDefaultConstructible> queue{5};
  // queue.push(NonDefaultConstructible{23});
  // resetCounters();

  // [[maybe_unused]] auto tmp = queue.pop();

  // REQUIRE(NonDefaultConstructible::nOfDtorCalls == 1);
}

TEST_CASE("Lvalue push copies element", "[Non-Default-Constructible Element Suite]") {
  // resetCounters();
  // BoundedQueue<NonDefaultConstructible> queue{5};
  // NonDefaultConstructible element{23};

  // queue.push(element);

  // REQUIRE(NonDefaultConstructible::nOfCopyConstructions == 1);
}

TEST_CASE("Rvalue push moves element", "[Non-Default-Constructible Element Suite]") {
  // resetCounters();
  // BoundedQueue<NonDefaultConstructible> queue{5};
  // NonDefaultConstructible element{23};

  // queue.push(std::move(element));

  // REQUIRE(NonDefaultConstructible::nOfMoveConstructions == 1);
}

TEST_CASE("Lvalue push must not copy assign", "[Non-Default-Constructible Element Suite]") {
  // BoundedQueue<NonDefaultConstructible> queue{5};
  // NonDefaultConstructible element{23};

  // resetCounters();
  // queue.push(element);

  // REQUIRE(NonDefaultConstructible::nOfCopyAssignments == 0);
}

TEST_CASE("Rvalue push must not move assign", "[Non-Default-Constructible Element Suite]") {
  // BoundedQueue<NonDefaultConstructible> queue{5};
  // NonDefaultConstructible element{23};

  // resetCounters();
  // queue.push(std::move(element));

  // REQUIRE(NonDefaultConstructible::nOfMoveAssignments == 0);
}
