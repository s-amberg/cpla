#include "BoundedBuffer.hpp"
#include "MemoryOperationCounter.hpp"

#include <catch2/catch_test_macros.hpp>
#include <stdexcept>


//--- a) ---


TEST_CASE("make_buffer() from rvalue argument contains one element", "MakeBuffer Suite") {
  // BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{});
  // REQUIRE(buffer.size() == 1);
}

TEST_CASE("make_buffer() from rvalue argument moves object", "MakeBuffer Suite") {
  // MemoryOperationCounter expected{1, 0, true};
  // BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{});
  // REQUIRE(expected == buffer.front());
}

TEST_CASE("make_buffer() from lvalue argument copies object", "MakeBuffer Suite") {
  // MemoryOperationCounter expected{0, 1, true};
  // MemoryOperationCounter insertee{};
  // BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(insertee);
  // REQUIRE(expected == buffer.front());
}

TEST_CASE("make_buffer() from const lvalue argument copies object", "MakeBuffer Suite") {
  // MemoryOperationCounter expected{0, 1, true};
  // MemoryOperationCounter const insertee{};
  // BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(insertee);
  // REQUIRE(expected == buffer.front());
}


//--- b) ---


TEST_CASE("make_buffer() from two rvalue arguments contains two elements", "MakeBuffer Suite") {
  // BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, MemoryOperationCounter{});
  // REQUIRE(buffer.size() == 2);
}

TEST_CASE("make_buffer() from two lvalue arguments contains two elements", "MakeBuffer Suite") {
  // MemoryOperationCounter element1{}, element2{};
  // BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(element1, element2);
  // REQUIRE(buffer.size() == 2);
}

TEST_CASE("make_buffer() from too many elements throws", "MakeBuffer Suite") {
  // REQUIRE_THROWS_AS((BoundedBuffer<int, 1>::make_buffer(1, 2)), std::invalid_argument);
}

TEST_CASE("make_buffer() from two rvalue arguments moves first element", "MakeBuffer Suite") {
  // MemoryOperationCounter expected{1, 0, true};
  // BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, MemoryOperationCounter{});
  // REQUIRE(expected == buffer.front());
}

TEST_CASE("make_buffer() from two rvalue arguments moves second element", "MakeBuffer Suite") {
  // MemoryOperationCounter expected{1, 0, true};
  // BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, MemoryOperationCounter{});
  // REQUIRE(expected == buffer.back());
}

TEST_CASE("make_buffer() from two mixed arguments copies first element", "MakeBuffer Suite") {
  // MemoryOperationCounter expected{0, 1, true};
  // MemoryOperationCounter lvalue{};
  // BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(lvalue, MemoryOperationCounter{});
  // REQUIRE(expected == buffer.front());
}

TEST_CASE("make_buffer() from two mixed arguments moves second element", "MakeBuffer Suite") {
  // MemoryOperationCounter expected{1, 0, true};
  // MemoryOperationCounter lvalue{};
  // BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(lvalue, MemoryOperationCounter{});
  // REQUIRE(expected == buffer.back());
}

TEST_CASE("make_buffer() from two mixed arguments moves first element", "MakeBuffer Suite") {
  // MemoryOperationCounter expected{1, 0, true};
  // MemoryOperationCounter lvalue{};
  // BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, lvalue);
  // REQUIRE(expected == buffer.front());
}

TEST_CASE("make_buffer() from two mixed arguments copies second element", "MakeBuffer Suite") {
  // MemoryOperationCounter expected{0, 1, true};
  // MemoryOperationCounter lvalue{};
  // BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, lvalue);
  // REQUIRE(expected == buffer.back());
}
