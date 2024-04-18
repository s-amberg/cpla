#include "BoundedQueueHeapMemorySuite.hpp"

#include <cute/cute.h>

// #include "BoundedQueue.hpp"
#include "TimesLiteral.hpp"

#include <cstddef>
#include <ios>
#include <stdexcept>
#include <utility>
#include <vector>

struct AllocationTracker {
  static auto operator new(std::size_t sz) -> void * {
    auto *ptr = static_cast<AllocationTracker *>(::operator new(sz));
    allocatedSingleObjects.push_back(ptr);
    return ptr;
  }

  static auto operator new[](std::size_t sz) -> void * {
    auto *ptr = static_cast<AllocationTracker *>(::operator new[](sz));
    allocatedArrays.push_back(ptr);
    return ptr;
  }

  static auto operator delete(void *ptr) -> void {
    deallocatedSingleObjects.push_back(static_cast<AllocationTracker *>(ptr));
    ::operator delete(ptr);
  }
  static auto operator delete[](void *ptr) -> void {
    deallocatedArrays.push_back(static_cast<AllocationTracker *>(ptr));
    ::operator delete[](ptr);
  }

  static auto operator new(std::size_t count, void *ptr) -> void * {
    return ::operator new(count, ptr);
  }

  static std::vector<AllocationTracker *> allocatedSingleObjects;
  static std::vector<AllocationTracker *> allocatedArrays;
  static std::vector<AllocationTracker *> deallocatedSingleObjects;
  static std::vector<AllocationTracker *> deallocatedArrays;
};

std::vector<AllocationTracker *> AllocationTracker::allocatedSingleObjects;
std::vector<AllocationTracker *> AllocationTracker::allocatedArrays;
std::vector<AllocationTracker *> AllocationTracker::deallocatedSingleObjects;
std::vector<AllocationTracker *> AllocationTracker::deallocatedArrays;

std::ostream &operator<<(std::ostream &out, AllocationTracker const *const ptr) {
  out << "0x" << std::hex << (unsigned long long)ptr << std::dec;
  return out;
}

void resetAllocationCounters() {
  AllocationTracker::allocatedSingleObjects.clear();
  AllocationTracker::allocatedArrays.clear();
  AllocationTracker::deallocatedSingleObjects.clear();
  AllocationTracker::deallocatedArrays.clear();
}

TEST(test_allocation_of_default_bounded_queue) {
  // resetAllocationCounters();
  // { BoundedQueue<AllocationTracker> queue{2}; }
  // ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

TEST(test_deallocation_of_default_bounded_queue) {
  // resetAllocationCounters();
  // { BoundedQueue<AllocationTracker> queue{2}; }
  // ASSERT_EQUAL(0, AllocationTracker::deallocatedArrays.size());
}

TEST(test_no_undeleted_allocation_on_exception) {
  // resetAllocationCounters();
  // try {
  //   BoundedQueue<AllocationTracker> queue{0};
  //   FAILM("The tests expects the BoundedQueue not being constructible with size 0.");
  // } catch (std::invalid_argument const &e) {
  //   ASSERT_EQUAL(AllocationTracker::deallocatedArrays, AllocationTracker::allocatedArrays);
  // }
}

TEST(test_copy_constructor_allocates_a_new_queue) {
  // resetAllocationCounters();
  // BoundedQueue<AllocationTracker> queue{15};
  // BoundedQueue<AllocationTracker> copy{queue};
  // ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

TEST(test_move_constructor_does_not_allocate_a_new_queue) {
  // resetAllocationCounters();
  // BoundedQueue<AllocationTracker> queue{15};
  // BoundedQueue<AllocationTracker> moved{std::move(queue)};
  // ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

TEST(test_copy_assignment_one_additional_allocation) {
  // resetAllocationCounters();
  // BoundedQueue<AllocationTracker> queue{3}, copy{2};
  // queue.push(AllocationTracker{});
  // queue.push(AllocationTracker{});
  // copy = queue;
  // ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

TEST(test_move_assignment_no_additional_allocation) {
  // resetAllocationCounters();
  // BoundedQueue<AllocationTracker> queue{3}, move{2};
  // queue.push(AllocationTracker{});
  // queue.push(AllocationTracker{});
  // move = std::move(queue);
  // ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

TEST(test_copy_self_assignment_no_additional_allocation) {
  // resetAllocationCounters();
  // BoundedQueue<AllocationTracker> queue{3};
  // queue.push(AllocationTracker{});
  // queue.push(AllocationTracker{});
  // queue = (queue);
  // ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

TEST(test_move_self_assignment_no_addtional_allocation) {
  // resetAllocationCounters();
  // BoundedQueue<AllocationTracker> queue{3};
  // queue.push(AllocationTracker{});
  // queue.push(AllocationTracker{});
  // queue = std::move(queue);
  // ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

struct CopyCounter {
  CopyCounter() = default;
  CopyCounter(CopyCounter const &other) {
    copy_counter++;
  }
  CopyCounter &operator=(CopyCounter const &other) {
    copy_counter++;
    return *this;
  }
  CopyCounter(CopyCounter &&) = default;
  CopyCounter &operator=(CopyCounter &&) = default;

  static unsigned copy_counter;
  static void resetCopyCounter() {
    copy_counter = 0;
  }
};

unsigned CopyCounter::copy_counter{0};

using namespace times::literal;

TEST(test_copy_only_initialized_elements_in_copy_construction) {
  // CopyCounter::resetCopyCounter();
  // BoundedQueue<CopyCounter> queue{100};
  // 100_times([&]() { queue.push(CopyCounter{}); });
  // 75_times([&]() { queue.pop(); });
  // 25_times([&]() { queue.push(CopyCounter{}); });
  // BoundedQueue<CopyCounter> copy{queue};
  // ASSERT_EQUAL(50, CopyCounter::copy_counter);
}

TEST(test_copy_only_initialized_elements_in_copy_assignment) {
  // CopyCounter::resetCopyCounter();
  // BoundedQueue<CopyCounter> queue{100}, copy{1};
  // 100_times([&]() { queue.push(CopyCounter{}); });
  // 75_times([&]() { queue.pop(); });
  // 25_times([&]() { queue.push(CopyCounter{}); });
  // copy = queue;
  // ASSERT_EQUAL(50, CopyCounter::copy_counter);
}

auto make_suite_bounded_queue_heap_memory_suite() -> cute::suite {
  return cute::suite{"BoundedQueue Heap Memory Suite",
                     {
                         test_allocation_of_default_bounded_queue,
                         test_deallocation_of_default_bounded_queue,
                         test_no_undeleted_allocation_on_exception,
                         test_copy_constructor_allocates_a_new_queue,
                         test_copy_self_assignment_no_additional_allocation,
                         test_move_self_assignment_no_addtional_allocation,
                         test_copy_only_initialized_elements_in_copy_construction,
                         test_copy_only_initialized_elements_in_copy_assignment,
                         test_move_constructor_does_not_allocate_a_new_queue,
                         test_copy_assignment_one_additional_allocation,
                         test_move_assignment_no_additional_allocation,
                     }};
}
