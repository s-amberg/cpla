#include "BoundedQueueMultiThreadedSuite.hpp"
#include <cute/cute.h>

// #include "BoundedQueue.hpp"
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <future>
#include <iterator>
#include <numeric>
#include <stdexcept>
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

// auto launchProducer(std::size_t start, std::size_t end, BoundedQueue<unsigned> &small_queue) -> std::future<void> {
//   return std::async(std::launch::async, [&, start, end]() mutable {
//     while (start < end) {
//       small_queue.push(start++);
//     }
//   });
// }

// template <typename T>
// auto launchConsumer(std::size_t nOfElements, BoundedQueue<T> &small_queue) -> std::future<std::vector<T>> {
//   return std::async(std::launch::async, [&, nOfElements]() {
//     std::vector<unsigned> popped_elements{};
//     for (auto i = 0u; i < nOfElements; i++) {
//       auto result = small_queue.pop();
//       popped_elements.push_back(result);
//     }
//     return popped_elements;
//   });
// }

TEST(test_one_producer_and_one_consumer) {
  //   const std::size_t nOfElements = 1000;
  //   std::vector<unsigned> expected(nOfElements, 0);
  //   std::iota(std::begin(expected), std::end(expected), 0);
  //   BoundedQueue<unsigned> small_queue{1};
  //   auto producer = launchProducer(0, nOfElements, small_queue);
  //   auto consumer = launchConsumer(nOfElements, small_queue);
  //   ASSERT_NOT_EQUAL_TO(std::future_status::timeout, producer.wait_for(std::chrono::seconds{1}));
  //   ASSERT_NOT_EQUAL_TO(std::future_status::timeout, consumer.wait_for(std::chrono::seconds{1}));
  //   std::vector<unsigned> popped_elements{consumer.get()};
  //   ASSERT_EQUAL(expected, popped_elements);
}

TEST(test_two_producers_and_one_consumer) {
  //   const std::size_t nOfElements = 1000;
  //   std::vector<unsigned> expected(nOfElements, 0);
  //   std::iota(std::begin(expected), std::end(expected), 0);
  //   BoundedQueue<unsigned> small_queue{10};
  //   auto producer1 = launchProducer(0, nOfElements / 2, small_queue);
  //   auto producer2 = launchProducer(nOfElements / 2, nOfElements, small_queue);
  //   auto consumer = launchConsumer(nOfElements, small_queue);

  //   ASSERT_NOT_EQUAL_TO(std::future_status::timeout, producer1.wait_for(std::chrono::seconds{1}));
  //   ASSERT_NOT_EQUAL_TO(std::future_status::timeout, producer2.wait_for(std::chrono::seconds{1}));
  //   ASSERT_NOT_EQUAL_TO(std::future_status::timeout, consumer.wait_for(std::chrono::seconds{1}));
  //   std::vector<unsigned> popped_elements{consumer.get()};
  //   std::sort(std::begin(popped_elements), std::end(popped_elements));
  //   ASSERT_EQUAL(expected, popped_elements);
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

TEST(test_one_producer_two_consumers) {
  //   const std::size_t nOfElements = 1000;
  //   std::vector<unsigned> expected(nOfElements, 0);
  //   std::iota(std::begin(expected), std::end(expected), 0);
  //   BoundedQueue<unsigned> small_queue{10};
  //   auto producer = launchProducer(0, nOfElements, small_queue);
  //   std::vector<std::future<std::vector<unsigned>>> consumers{};
  //   consumers.push_back(launchConsumer(nOfElements / 2, small_queue));
  //   consumers.push_back(launchConsumer(nOfElements / 2, small_queue));

  //   ASSERT_NOT_EQUAL_TO(std::future_status::timeout, producer.wait_for(std::chrono::seconds{1}));
  //   for (auto &consumer : consumers) {
  //     ASSERT_NOT_EQUAL_TO(std::future_status::timeout, consumer.wait_for(std::chrono::seconds{1}));
  //   }

  //   std::vector<unsigned> popped_elements{combine_and_sort(consumers)};
  //   ASSERT_EQUAL(expected, popped_elements);
}

TEST(test_ten_producers_ten_consumers) {
  //   const std::size_t nOfElements = 10000;
  //   const std::size_t sliceSize = nOfElements / 10;
  //   std::vector<unsigned> expected(nOfElements, 0);
  //   std::iota(std::begin(expected), std::end(expected), 0);
  //   BoundedQueue<unsigned> queue{10};
  //   std::vector<std::future<void>> producers{};
  //   std::vector<std::future<std::vector<unsigned>>> consumers{};
  //   for (auto i = 0u; i < 10; i++) {
  //     producers.push_back(launchProducer(sliceSize * i, sliceSize * (i + 1), queue));
  //     consumers.push_back(launchConsumer(sliceSize, queue));
  //   }

  //   for (auto &producer : producers) {
  //     ASSERT_NOT_EQUAL_TO(std::future_status::timeout, producer.wait_for(std::chrono::seconds{1}));
  //   }
  //   for (auto &consumer : consumers) {
  //     ASSERT_NOT_EQUAL_TO(std::future_status::timeout, consumer.wait_for(std::chrono::seconds{1}));
  //   }

  //   std::vector<unsigned> popped_elements{combine_and_sort(consumers)};
  //   ASSERT_EQUAL(expected, popped_elements);
}

TEST(test_blocked_produced_unblocks) {
  //   BoundedQueue<unsigned> queue{1};
  //   queue.push(1);

  //   auto f = std::async(std::launch::async, [&]() {
  //     std::this_thread::sleep_for(std::chrono::milliseconds{50});
  //     queue.pop();
  //   });

  //   queue.push(2);
  //   ASSERT_EQUAL(2, queue.pop());
}

TEST(test_blocked_consumer_unblocks) {
  //   BoundedQueue<unsigned> queue{1};

  //   auto f = std::async(std::launch::async, [&]() {
  //     std::this_thread::sleep_for(std::chrono::milliseconds{50});
  //     queue.push(1);
  //   });

  //   ASSERT_EQUAL(1, queue.pop());
}

auto make_suite_bounded_queue_multi_threaded_suite() -> cute::suite {
  return cute::suite{"BoundedQueue Multi Threaded Suite",
                     {
                         test_one_producer_and_one_consumer,
                         test_two_producers_and_one_consumer,
                         test_one_producer_two_consumers,
                         test_ten_producers_ten_consumers,
                         test_blocked_produced_unblocks,
                         test_blocked_consumer_unblocks,
                     }};
}
