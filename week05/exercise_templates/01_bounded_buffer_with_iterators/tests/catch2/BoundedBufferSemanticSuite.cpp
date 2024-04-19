
#include "BoundedBuffer.hpp"

#include "MemoryOperationCounter.hpp"

#include <catch2/catch_test_macros.hpp>
#include <utility>

TEST_CASE("push(lvalue) copies element", "[Semantic Suite]") {
   BoundedBuffer<MemoryOperationCounter> buffer{1};
   MemoryOperationCounter counter{}, expected{0, 1, true};
   buffer.push(counter);
   REQUIRE(expected == buffer.front());
}

TEST_CASE("push(rvalue) moves element", "[Semantic Suite]") {
   BoundedBuffer<MemoryOperationCounter> buffer{1};
   MemoryOperationCounter counter{}, expected{1, 0, true};
   buffer.push(std::move(counter));
   REQUIRE(expected == buffer.front());
}

TEST_CASE("Element in BoundedBuffer is copied along copy constructor", "[Semantic Suite]") {
   BoundedBuffer<MemoryOperationCounter> buffer{1};
   MemoryOperationCounter counter{}, expected{0, 2, true};
   buffer.push(counter);
   BoundedBuffer<MemoryOperationCounter> const &constBuffer = buffer;
   BoundedBuffer<MemoryOperationCounter> bufferCopied{constBuffer};
   REQUIRE(expected == bufferCopied.front());
}

TEST_CASE("Element in BoundedBuffer is copied along copy assignment operator", "[Semantic Suite]") {
   BoundedBuffer<MemoryOperationCounter> buffer{1}, bufferCopied{1};
   MemoryOperationCounter counter{}, expected{0, 2, true};
   buffer.push(counter);
   BoundedBuffer<MemoryOperationCounter> const &constBuffer = buffer;
   bufferCopied = constBuffer;
   REQUIRE(expected == bufferCopied.front());
}

TEST_CASE("Element in BoundedBuffer is moved along move constructor", "[Semantic Suite]") {
   BoundedBuffer<MemoryOperationCounter> buffer{1};
   MemoryOperationCounter counter{}, expected{1, 0, true};
   buffer.push(std::move(counter));
   BoundedBuffer<MemoryOperationCounter> bufferCopied{std::move(buffer)};
   REQUIRE(expected == bufferCopied.front());
}

TEST_CASE("Element in BoundedBuffer is moved along move assignment operator", "[Semantic Suite]") {
   BoundedBuffer<MemoryOperationCounter> buffer{1}, bufferMoved{1};
   MemoryOperationCounter counter{}, expected{1, 0, true};
   buffer.push(std::move(counter));
   bufferMoved = std::move(buffer);
   REQUIRE(expected == bufferMoved.front());
}

TEST_CASE("Element in BoundedBuffer is copied along copy assignment operator in multiple copies", "[Semantic Suite]") {
   BoundedBuffer<MemoryOperationCounter> buffer{1}, intermediate1{1}, intermediate2{1}, bufferCopied{1};
   MemoryOperationCounter counter{}, expected{0, 4, true};
   buffer.push(counter);
   bufferCopied = intermediate2 = intermediate1 = buffer;
   REQUIRE(expected == bufferCopied.front());
}

TEST_CASE("Element in BoundedBuffer is moved along move assignment operator in multiple moves", "[Semantic Suite]") {
   BoundedBuffer<MemoryOperationCounter> buffer{1}, intermediate1{1}, intermediate2{1}, bufferMoved{1};
   MemoryOperationCounter counter{}, expected{1, 0, true};
   buffer.push(std::move(counter));
   bufferMoved = std::move(intermediate1 = std::move(intermediate2 = std::move(buffer)));
   REQUIRE(expected == bufferMoved.front());
}

TEST_CASE("BoundedBuffer copied is returned from assignment", "[Semantic Suite]") {
   BoundedBuffer<MemoryOperationCounter> buffer{1}, bufferCopied{1};
   MemoryOperationCounter counter{}, expected{0, 2, true};
   buffer.push(counter);
   BoundedBuffer<MemoryOperationCounter> const &constBuffer = buffer;
   REQUIRE(expected == (bufferCopied = constBuffer).front());
}

TEST_CASE("BoundedBuffer moved is returned from assignment", "[Semantic Suite]") {
   BoundedBuffer<MemoryOperationCounter> buffer{1}, bufferMoved{1};
   MemoryOperationCounter counter{}, expected{1, 0, true};
   buffer.push(std::move(counter));
   REQUIRE(expected == (bufferMoved = std::move(buffer)).front());
}


TEST_CASE("Capacity is copied in Constructor", "[Semantic Suite]") {
//   given
  BoundedBuffer<MemoryOperationCounter> buffer{4};
  buffer.push(MemoryOperationCounter{});
  buffer.push(MemoryOperationCounter{});

//   when
  BoundedBuffer<MemoryOperationCounter> copy{buffer};
  copy.push(MemoryOperationCounter{});
  copy.push(MemoryOperationCounter{});

//   then
  REQUIRE(copy.full());
}

TEST_CASE("Capacity is copied in Assignment", "[Semantic Suite]") {
//   given
  BoundedBuffer<MemoryOperationCounter> buffer{4}, copy{1};
  buffer.push(MemoryOperationCounter{});
  buffer.push(MemoryOperationCounter{});

//   when
  copy = buffer;
  copy.push(MemoryOperationCounter{});
  copy.push(MemoryOperationCounter{});

//   then
  REQUIRE(copy.full());
}

TEST_CASE("Capacity is moved in Constructor", "[Semantic Suite]") {
//   given
  BoundedBuffer<MemoryOperationCounter> buffer{4};
  buffer.push(MemoryOperationCounter{});
  buffer.push(MemoryOperationCounter{});

//   when
  BoundedBuffer<MemoryOperationCounter> copy{std::move(buffer)};
  copy.push(MemoryOperationCounter{});
  copy.push(MemoryOperationCounter{});

//   then
  REQUIRE(copy.full());
}

TEST_CASE("Capacity is moved in Assignment", "[Semantic Suite]") {
//   given
  BoundedBuffer<MemoryOperationCounter> buffer{4}, copy{1};
  buffer.push(MemoryOperationCounter{});
  buffer.push(MemoryOperationCounter{});

//   when
  copy = std::move(buffer);
  copy.push(MemoryOperationCounter{});
  copy.push(MemoryOperationCounter{});

//   then
  REQUIRE(copy.full());
}