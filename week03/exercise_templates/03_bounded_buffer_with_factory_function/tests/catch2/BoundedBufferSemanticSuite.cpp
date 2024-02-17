
#include "BoundedBuffer.hpp"

#include "MemoryOperationCounter.hpp"

#include <catch2/catch_test_macros.hpp>
#include <utility>

TEST_CASE("push(lvalue) copies element", "[Semantic Suite]") {
  // BoundedBuffer<MemoryOperationCounter, 1> buffer{};
  // MemoryOperationCounter counter{}, expected{0, 1, true};
  // buffer.push(counter);
  // REQUIRE(expected == buffer.front());
}

TEST_CASE("push(rvalue) moves element", "[Semantic Suite]") {
  // BoundedBuffer<MemoryOperationCounter, 1> buffer{};
  // MemoryOperationCounter counter{}, expected{1, 0, true};
  // buffer.push(std::move(counter));
  // REQUIRE(expected == buffer.front());
}

TEST_CASE("Element in BoundedBuffer is copied along copy constructor", "[Semantic Suite]") {
  // BoundedBuffer<MemoryOperationCounter, 1> buffer{};
  // MemoryOperationCounter counter{}, expected{0, 2, true};
  // buffer.push(counter);
  // BoundedBuffer<MemoryOperationCounter, 1> const &constBuffer = buffer;
  // BoundedBuffer<MemoryOperationCounter, 1> bufferCopied{constBuffer};
  // REQUIRE(expected == bufferCopied.front());
}

TEST_CASE("Element in BoundedBuffer is copied along copy assignment operator", "[Semantic Suite]") {
  // BoundedBuffer<MemoryOperationCounter, 1> buffer{}, bufferCopied{};
  // MemoryOperationCounter counter{}, expected{0, 2, true};
  // buffer.push(counter);
  // BoundedBuffer<MemoryOperationCounter, 1> const &constBuffer = buffer;
  // bufferCopied = constBuffer;
  // REQUIRE(expected == bufferCopied.front());
}

TEST_CASE("Element in BoundedBuffer is moved along move constructor", "[Semantic Suite]") {
  // BoundedBuffer<MemoryOperationCounter, 1> buffer{};
  // MemoryOperationCounter counter{}, expected{2, 0, true};
  // buffer.push(std::move(counter));
  // BoundedBuffer<MemoryOperationCounter, 1> bufferCopied{std::move(buffer)};
  // REQUIRE(expected == bufferCopied.front());
}

TEST_CASE("Element in BoundedBuffer is moved along move assignment operator", "[Semantic Suite]") {
  // BoundedBuffer<MemoryOperationCounter, 1> buffer{}, bufferMoved{};
  // MemoryOperationCounter counter{}, expected{2, 0, true};
  // buffer.push(std::move(counter));
  // bufferMoved = std::move(buffer);
  // REQUIRE(expected == bufferMoved.front());
}

TEST_CASE("Element in BoundedBuffer is copied along copy assignment operator in multiple copies", "[Semantic Suite]") {
  // BoundedBuffer<MemoryOperationCounter, 1> buffer{}, intermediate1{}, intermediate2{}, bufferCopied{};
  // MemoryOperationCounter counter{}, expected{0, 4, true};
  // buffer.push(counter);
  // bufferCopied = intermediate2 = intermediate1 = buffer;
  // REQUIRE(expected == bufferCopied.front());
}

TEST_CASE("Element in BoundedBuffer is moved along move assignment operator in multiple moves", "[Semantic Suite]") {
  // BoundedBuffer<MemoryOperationCounter, 1> buffer{}, intermediate1{}, intermediate2{}, bufferMoved{};
  // MemoryOperationCounter counter{}, expected{4, 0, true};
  // buffer.push(std::move(counter));
  // bufferMoved = std::move(intermediate1 = std::move(intermediate2 = std::move(buffer)));
  // REQUIRE(expected == bufferMoved.front());
}

TEST_CASE("BoundedBuffer copied is returned from assignment", "[Semantic Suite]") {
  // BoundedBuffer<MemoryOperationCounter, 1> buffer{}, bufferCopied{};
  // MemoryOperationCounter counter{}, expected{0, 2, true};
  // buffer.push(counter);
  // BoundedBuffer<MemoryOperationCounter, 1> const &constBuffer = buffer;
  // REQUIRE(expected == (bufferCopied = constBuffer).front());
}

TEST_CASE("BoundedBuffer moved is returned from assignment", "[Semantic Suite]") {
  // BoundedBuffer<MemoryOperationCounter, 1> buffer{}, bufferMoved{};
  // MemoryOperationCounter counter{}, expected{2, 0, true};
  // buffer.push(std::move(counter));
  // REQUIRE(expected == (bufferMoved = std::move(buffer)).front());
}
