#include "BoundedBuffer.hpp"

#include <catch2/catch_test_macros.hpp>

#include <stdexcept>
#include <string>
#include <utility>


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

TEST_CASE("New buffer of non-default constructible invokes no destructors", "[Non-Default-Constructible Element Suite]") {
  resetCounters();
  BoundedBuffer<NonDefaultConstructible> buffer{5};
  REQUIRE(NonDefaultConstructible::nOfDtorCalls == 0);
}

TEST_CASE("Element in buffer is destroyed once", "[Non-Default-Constructible Element Suite]") {
  {
    BoundedBuffer<NonDefaultConstructible> buffer{5};
    buffer.push(NonDefaultConstructible{23});
    resetCounters();
  }
  REQUIRE(NonDefaultConstructible::nOfDtorCalls == 1);
}

TEST_CASE("Element in moved buffer is destroyed once", "[Non-Default-Constructible Element Suite]") {
  {
    BoundedBuffer<NonDefaultConstructible> buffer{5};
    buffer.push(NonDefaultConstructible{23});
    resetCounters();

    BoundedBuffer<NonDefaultConstructible> moved{std::move(buffer)};
  }

  REQUIRE(NonDefaultConstructible::nOfDtorCalls == 1);
}

TEST_CASE("Every element in copied buffer is destroyed once", "[Non-Default-Constructible Element Suite]") {
  {
    BoundedBuffer<NonDefaultConstructible> buffer{5};
    buffer.push(NonDefaultConstructible{23});
    resetCounters();
    REQUIRE_FALSE(buffer.empty());

    BoundedBuffer<NonDefaultConstructible> copy{buffer};
    REQUIRE_FALSE(buffer.empty());
    REQUIRE_FALSE(copy.empty());
  }
  REQUIRE(NonDefaultConstructible::nOfDtorCalls == 2);
}

TEST_CASE("Pop destroys element", "[Non-Default-Constructible Element Suite]") {
  BoundedBuffer<NonDefaultConstructible> buffer{5};
  buffer.push(NonDefaultConstructible{23});
  resetCounters();

  buffer.pop();

  REQUIRE(NonDefaultConstructible::nOfDtorCalls == 1);
}

TEST_CASE("Lvalue push copies element", "[Non-Default-Constructible Element Suite]") {
  resetCounters();
  BoundedBuffer<NonDefaultConstructible> buffer{5};
  NonDefaultConstructible element{23};

  buffer.push(element);

  REQUIRE(NonDefaultConstructible::nOfCopyConstructions == 1);
}

TEST_CASE("Rvalue push moves element", "[Non-Default-Constructible Element Suite]") {
  resetCounters();
  BoundedBuffer<NonDefaultConstructible> buffer{5};
  NonDefaultConstructible element{23};

  buffer.push(std::move(element));

  REQUIRE(NonDefaultConstructible::nOfMoveConstructions == 1);
}

TEST_CASE("Lvalue push must not copy assign", "[Non-Default-Constructible Element Suite]") {
  BoundedBuffer<NonDefaultConstructible> buffer{5};
  NonDefaultConstructible element{23};

  resetCounters();
  buffer.push(element);

  REQUIRE(NonDefaultConstructible::nOfCopyAssignments == 0);
}

TEST_CASE("Rvalue push must not move assign", "[Non-Default-Constructible Element Suite]") {
  BoundedBuffer<NonDefaultConstructible> buffer{5};
  NonDefaultConstructible element{23};

  resetCounters();
  buffer.push(std::move(element));

  REQUIRE(NonDefaultConstructible::nOfMoveAssignments == 0);
}