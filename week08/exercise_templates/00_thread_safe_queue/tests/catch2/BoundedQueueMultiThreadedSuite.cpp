#include "BoundedQueue.hpp"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <future>
#include <iterator>
#include <numeric>
#include <ostream>
#include <thread>
#include <vector>

namespace std {
auto operator<<(std::ostream &out, std::future_status const &status) -> std::ostream & {
  switch (status) {
  case std::future_status::ready:
    out << "ready";
    break;
  case std::future_status::timeout:
    out << "timeout";
    break;
  case std::future_status::deferred:
    out << "deferred";
    break;
  default:
    out << "unknown";
    break;
  }
  return out;
}

} // namespace std

auto launchProducer(std::size_t start, std::size_t end, BoundedQueue<unsigned> &small_queue) -> std::future<void> {
  return std::async(std::launch::async, [&, start, end]() mutable {
    while (start < end) {
      small_queue.push(start++);
    }
  });
}

template <typename T>
auto launchConsumer(std::size_t nOfElements, BoundedQueue<T> &small_queue) -> std::future<std::vector<T>> {
  return std::async(std::launch::async, [&, nOfElements]() {
    std::vector<unsigned> popped_elements{};
    for (auto i = 0u; i < nOfElements; i++) {
      auto result = small_queue.pop();
      popped_elements.push_back(result);
    }
    return popped_elements;
  });
}

TEST_CASE("One producer and oe consumer", "[Multi Threaded Suite]") {
  const std::size_t nOfElements = 1000;
  std::vector<unsigned> expected(nOfElements, 0);
  std::iota(std::begin(expected), std::end(expected), 0);
  BoundedQueue<unsigned> small_queue{1};
  auto producer = launchProducer(0, nOfElements, small_queue);
  auto consumer = launchConsumer(nOfElements, small_queue);
  REQUIRE(producer.wait_for(std::chrono::seconds{1}) != std::future_status::timeout);
  REQUIRE(consumer.wait_for(std::chrono::seconds{1}) != std::future_status::timeout);
  std::vector<unsigned> popped_elements{consumer.get()};
  REQUIRE(popped_elements == expected);
}

TEST_CASE("Two producers and one consumer", "[Multi Threaded Suite]") {
  const std::size_t nOfElements = 1000;
  std::vector<unsigned> expected(nOfElements, 0);
  std::iota(std::begin(expected), std::end(expected), 0);
  BoundedQueue<unsigned> small_queue{10};
  auto producer1 = launchProducer(0, nOfElements / 2, small_queue);
  auto producer2 = launchProducer(nOfElements / 2, nOfElements, small_queue);
  auto consumer = launchConsumer(nOfElements, small_queue);

  REQUIRE(producer1.wait_for(std::chrono::seconds{1}) != std::future_status::timeout);
  REQUIRE(producer2.wait_for(std::chrono::seconds{1}) != std::future_status::timeout);
  REQUIRE(consumer.wait_for(std::chrono::seconds{1}) != std::future_status::timeout);
  std::vector<unsigned> popped_elements{consumer.get()};
  std::sort(std::begin(popped_elements), std::end(popped_elements));
  REQUIRE(popped_elements == expected);
}

template <typename T>
auto combine_and_sort(std::vector<std::future<std::vector<T>>> &parts) -> std::vector<T> {
  std::vector<T> result{};
  for (auto &part : parts) {
    auto values = part.get();
    std::copy(std::begin(values), std::end(values), std::back_inserter(result));
  }
  std::sort(std::begin(result), std::end(result));
  return result;
}

TEST_CASE("One producer and two consumers", "[Multi Threaded Suite]") {
  // const std::size_t nOfElements = 1000;
  // std::vector<unsigned> expected(nOfElements, 0);
  // std::iota(std::begin(expected), std::end(expected), 0);
  // BoundedQueue<unsigned> small_queue{10};
  // auto producer = launchProducer(0, nOfElements, small_queue);
  // std::vector<std::future<std::vector<unsigned>>> consumers{};
  // consumers.push_back(launchConsumer(nOfElements / 2, small_queue));
  // consumers.push_back(launchConsumer(nOfElements / 2, small_queue));

  // REQUIRE(producer.wait_for(std::chrono::seconds{1}) != std::future_status::timeout);
  // for (auto &consumer : consumers) {
  //   REQUIRE(consumer.wait_for(std::chrono::seconds{1}) != std::future_status::timeout);
  // }

  // std::vector<unsigned> popped_elements{combine_and_sort(consumers)};
  // REQUIRE(popped_elements == expected);
}

TEST_CASE("Ten producers and ten consumers", "[Multi Threaded Suite]") {
  // const std::size_t nOfElements = 10000;
  // const std::size_t sliceSize = nOfElements / 10;
  // std::vector<unsigned> expected(nOfElements, 0);
  // std::iota(std::begin(expected), std::end(expected), 0);
  // BoundedQueue<unsigned> queue{10};
  // std::vector<std::future<void>> producers{};
  // std::vector<std::future<std::vector<unsigned>>> consumers{};
  // for (auto i = 0u; i < 10; i++) {
  //   producers.push_back(launchProducer(sliceSize * i, sliceSize * (i + 1), queue));
  //   consumers.push_back(launchConsumer(sliceSize, queue));
  // }

  // for (auto &producer : producers) {
  //   REQUIRE(producer.wait_for(std::chrono::seconds{1}) != std::future_status::timeout);
  // }
  // for (auto &consumer : consumers) {
  //   REQUIRE(consumer.wait_for(std::chrono::seconds{1}) != std::future_status::timeout);
  // }

  // std::vector<unsigned> popped_elements{combine_and_sort(consumers)};
  // REQUIRE(popped_elements == expected);
}

TEST_CASE("Blocked producer unblocks", "[Multi Threaded Suite]") {
  // BoundedQueue<unsigned> queue{1};
  // queue.push(1);

  // auto f = std::async(std::launch::async, [&]() {
  //   std::this_thread::sleep_for(std::chrono::milliseconds{50});
  //   queue.pop();
  // });

  // queue.push(2);
  // REQUIRE(queue.pop() == 2);
}

TEST_CASE("Blocked consumer producer unblocks", "[Multi Threaded Suite]") {
  // BoundedQueue<unsigned> queue{1};

  // auto f = std::async(std::launch::async, [&]() {
  //   std::this_thread::sleep_for(std::chrono::milliseconds{50});
  //   queue.push(1);
  // });

  // REQUIRE(queue.pop() == 1);
}
