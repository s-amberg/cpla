// #include "BoundedQueue.hpp"

#include "MemoryOperationCounter.hpp"

#include <catch2/catch_test_macros.hpp>

#include <utility>

TEST_CASE("Queue push copies element", "[Semantic Suite]") {
  // BoundedQueue<MemoryOperationCounter> queue{1};
  // MemoryOperationCounter counter{}, expected{1, 1, true};
  // queue.push(counter);
  // REQUIRE(queue.pop() == expected);
}

TEST_CASE("Queue push moves element", "[Semantic Suite]") {
  // BoundedQueue<MemoryOperationCounter> queue{1};
  // MemoryOperationCounter counter{}, expected{2, 0, true};
  // queue.push(std::move(counter));
  // REQUIRE(queue.pop() == expected);
}

TEST_CASE("Element in Queue is copied along copy constructor", "[Semantic Suite]") {
  // BoundedQueue<MemoryOperationCounter> queue{1};
  // MemoryOperationCounter counter{}, expected{1, 2, true};
  // queue.push(counter);
  // BoundedQueue<MemoryOperationCounter> const &constQueue = queue;
  // BoundedQueue<MemoryOperationCounter> queueCopied{constQueue};
  // REQUIRE(queueCopied.pop() == expected);
}

TEST_CASE("Element in Queue is copied along copy assignment operator", "[Semantic Suite]") {
  // BoundedQueue<MemoryOperationCounter> queue{1}, queueCopied{1};
  // MemoryOperationCounter counter{}, expected{1, 2, true};
  // queue.push(counter);
  // BoundedQueue<MemoryOperationCounter> const &constQueue = queue;
  // queueCopied = constQueue;
  // REQUIRE(queueCopied.pop() == expected);
}

TEST_CASE("Element in Queue is moved along move constructor", "[Semantic Suite]") {
  // BoundedQueue<MemoryOperationCounter> queue{1};
  // MemoryOperationCounter counter{}, expected{2, 0, true};
  // queue.push(std::move(counter));
  // BoundedQueue<MemoryOperationCounter> queueMoved{std::move(queue)};
  // REQUIRE(queueMoved.pop() == expected);
}

TEST_CASE("Element in Queue is moved along move assignment operator", "[Semantic Suite]") {
  // BoundedQueue<MemoryOperationCounter> queue{1}, queueMoved{1};
  // MemoryOperationCounter counter{}, expected{2, 0, true};
  // queue.push(std::move(counter));
  // queueMoved = std::move(queue);
  // REQUIRE(queueMoved.pop() == expected);
}

TEST_CASE("Element in Queue is copied along assignment operator multiple copies", "[Semantic Suite]") {
  // BoundedQueue<MemoryOperationCounter> queue{1}, intermediate1{1}, intermediate2{1}, queueCopied{1};
  // MemoryOperationCounter counter{}, expected{1, 4, true};
  // queue.push(counter);
  // queueCopied = intermediate2 = intermediate1 = queue;
  // REQUIRE(queueCopied.pop() == expected);
}

TEST_CASE("Element in Queue is moved along assignment operator multiple moves", "[Semantic Suite]") {
  // BoundedQueue<MemoryOperationCounter> queue{1}, intermediate1{1}, intermediate2{1}, queueMoved{1};
  // MemoryOperationCounter counter{}, expected{2, 0, true};
  // queue.push(std::move(counter));
  // queueMoved = std::move(intermediate1 = std::move(intermediate2 = std::move(queue)));
  // REQUIRE(queueMoved.pop() == expected);
}

TEST_CASE("Queue copy is returned from assignment", "[Semantic Suite]") {
  // BoundedQueue<MemoryOperationCounter> queue{1}, queueCopied{1};
  // MemoryOperationCounter counter{}, expected{1, 2, true};
  // queue.push(counter);
  // BoundedQueue<MemoryOperationCounter> const &constQueue = queue;
  // REQUIRE((queueCopied = constQueue).pop() == expected);
}

TEST_CASE("Queue moved is returned from assignment", "[Semantic Suite]") {
  // BoundedQueue<MemoryOperationCounter> queue{1}, queueMoved{1};
  // MemoryOperationCounter counter{}, expected{2, 0, true};
  // queue.push(std::move(counter));
  // REQUIRE((queueMoved = std::move(queue)).pop() == expected);
}

TEST_CASE("Capacity is copied in ctor", "[Semantic Suite]") {
  // // given
  // BoundedQueue<MemoryOperationCounter> queue{4};
  // queue.push(MemoryOperationCounter{});
  // queue.push(MemoryOperationCounter{});

  // // when
  // BoundedQueue<MemoryOperationCounter> copy{queue};
  // copy.push(MemoryOperationCounter{});
  // copy.push(MemoryOperationCounter{});

  // // then
  // REQUIRE(copy.full());
}

TEST_CASE("Capacity is copied in assignment", "[Semantic Suite]") {
  // // given
  // BoundedQueue<MemoryOperationCounter> queue{4}, copy{1};
  // queue.push(MemoryOperationCounter{});
  // queue.push(MemoryOperationCounter{});

  // // when
  // copy = queue;
  // copy.push(MemoryOperationCounter{});
  // copy.push(MemoryOperationCounter{});

  // // then
  // REQUIRE(copy.full());
}

TEST_CASE("Capacity is moved in ctor", "[Semantic Suite]") {
  // // given
  // BoundedQueue<MemoryOperationCounter> queue{4};
  // queue.push(MemoryOperationCounter{});
  // queue.push(MemoryOperationCounter{});

  // // when
  // BoundedQueue<MemoryOperationCounter> copy{std::move(queue)};
  // copy.push(MemoryOperationCounter{});
  // copy.push(MemoryOperationCounter{});

  // // then
  // REQUIRE(copy.full());
}

TEST_CASE("Capacity is moved in assignment", "[Semantic Suite]") {
  // // given
  // BoundedQueue<MemoryOperationCounter> queue{4}, copy{1};
  // queue.push(MemoryOperationCounter{});
  // queue.push(MemoryOperationCounter{});

  // // when
  // copy = std::move(queue);
  // copy.push(MemoryOperationCounter{});
  // copy.push(MemoryOperationCounter{});

  // // then
  // REQUIRE(copy.full());
}
