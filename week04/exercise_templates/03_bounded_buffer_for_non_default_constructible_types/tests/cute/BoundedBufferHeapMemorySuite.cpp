#include "BoundedBufferHeapMemorySuite.hpp"
#include "BoundedBuffer.hpp"

#include "NTimes.hpp"

#include <cute/cute_suite.h>

#include <cstddef>
#include <ios>
#include <ostream>
#include <utility>
#include <vector>

struct AllocationTracker {
  static auto operator new(std::size_t sz) -> void* {
    auto ptr =
        static_cast<AllocationTracker*>(::operator new(sz));
    allocatedSingleObjects.push_back(ptr);
    return ptr;
  }
  static auto operator new[](std::size_t sz) -> void* {
    auto ptr =
        static_cast<AllocationTracker*>(::operator new[](sz));
    allocatedArrays.push_back(ptr);
    return ptr;
  }
  static void operator delete(void* ptr) {
    deallocatedSingleObjects.push_back(static_cast<AllocationTracker*>(ptr));
    ::operator delete(ptr);
  }
  static void operator delete[](void* ptr) {
    deallocatedArrays.push_back(static_cast<AllocationTracker*>(ptr));
    ::operator delete[](ptr);
  }

  static auto operator new(std::size_t sz, AllocationTracker* ptr) -> void* {
    (void)::operator new(sz, ptr);
    allocatedSingleObjects.push_back(ptr);
    return ptr;
  }

  static std::vector<AllocationTracker*> allocatedSingleObjects;
  static std::vector<AllocationTracker*> allocatedArrays;
  static std::vector<AllocationTracker*> deallocatedSingleObjects;
  static std::vector<AllocationTracker*> deallocatedArrays;
};

std::vector<AllocationTracker*> AllocationTracker::allocatedSingleObjects;
std::vector<AllocationTracker*> AllocationTracker::allocatedArrays;
std::vector<AllocationTracker*> AllocationTracker::deallocatedSingleObjects;
std::vector<AllocationTracker*> AllocationTracker::deallocatedArrays;

auto operator<<(std::ostream& out,
                         AllocationTracker const* const ptr) -> std::ostream& {
  out << "0x" << std::hex << (unsigned long long)ptr << std::dec;
  return out;
}

auto resetAllocationTrackers() -> void{
  AllocationTracker::allocatedSingleObjects.clear();
  AllocationTracker::allocatedArrays.clear();
  AllocationTracker::deallocatedSingleObjects.clear();
  AllocationTracker::deallocatedArrays.clear();
}

TEST(test_allocation_of_default_bounded_buffer) {
//   resetAllocationTrackers();
//   { BoundedBuffer<AllocationTracker> buffer{2}; }
//   ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

TEST(test_deallocation_of_default_bounded_buffer) {
//   resetAllocationTrackers();
//   { BoundedBuffer<AllocationTracker> buffer{2}; }
//   ASSERT_EQUAL(0, AllocationTracker::deallocatedArrays.size());
}

TEST(test_no_undeleted_allocation_on_exception) {
//   resetAllocationTrackers();
//   try {
//     BoundedBuffer<AllocationTracker> buffer{0};
//     FAILM(
//         "The tests expects the BoundedBuffer not being constructible with size "
//         "0.");
//   } catch (std::invalid_argument& e) {
//     ASSERT_EQUAL(AllocationTracker::deallocatedArrays,
//                  AllocationTracker::allocatedArrays);
//   }
}

TEST(test_copy_constructor_allocates_a_new_buffer) {
//   resetAllocationTrackers();
//   BoundedBuffer<AllocationTracker> buffer{15};
//   BoundedBuffer<AllocationTracker> copy{buffer};
//   ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

TEST(test_move_constructor_does_not_allocate_a_new_buffer) {
//   resetAllocationTrackers();
//   BoundedBuffer<AllocationTracker> buffer{15};
//   BoundedBuffer<AllocationTracker> moved{std::move(buffer)};
//   ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

TEST(test_copy_assignment_one_additional_allocation) {
//   resetAllocationTrackers();
//   BoundedBuffer<AllocationTracker> buffer{3}, copy{2};
//   buffer.push(AllocationTracker{});
//   buffer.push(AllocationTracker{});
//   copy = buffer;
//   ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

TEST(test_move_assignment_no_additional_allocation) {
//   resetAllocationTrackers();
//   BoundedBuffer<AllocationTracker> buffer{3}, move{2};
//   buffer.push(AllocationTracker{});
//   buffer.push(AllocationTracker{});
//   move = std::move(buffer);
//   ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

TEST(test_copy_self_assignment_no_additional_allocation) {
//   resetAllocationTrackers();
//   BoundedBuffer<AllocationTracker> buffer{3};
//   buffer.push(AllocationTracker{});
//   buffer.push(AllocationTracker{});
//   buffer = (buffer);
//   ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

TEST(test_move_self_assignment_no_addtional_allocation) {
//   resetAllocationTrackers();
//   BoundedBuffer<AllocationTracker> buffer{3};
//   buffer.push(AllocationTracker{});
//   buffer.push(AllocationTracker{});
//   buffer = std::move(buffer);
//   ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

struct CopyCounter {
  CopyCounter() = default;
  CopyCounter(CopyCounter const& other) { copy_counter++; }
  auto operator=(CopyCounter const& other) -> CopyCounter& {
    copy_counter++;
    return *this;
  }
  CopyCounter(CopyCounter&&) = default;
  auto operator=(CopyCounter&&) -> CopyCounter& = default;

  static unsigned copy_counter;
  static auto resetCopyCounter() -> void { copy_counter = 0; }
};

unsigned CopyCounter::copy_counter{0};

using namespace cpp_advanced::times_literal;

TEST(test_copy_only_initialized_elements_in_copy_construction) {
//   CopyCounter::resetCopyCounter();
//   BoundedBuffer<CopyCounter> buffer{100};
//   100_times([&]() { buffer.push(CopyCounter{}); });
//   75_times([&]() { buffer.pop(); });
//   25_times([&]() { buffer.push(CopyCounter{}); });
//   BoundedBuffer<CopyCounter> copy{buffer};
//   ASSERT_EQUAL(50, CopyCounter::copy_counter);
}

TEST(test_copy_only_initialized_elements_in_copy_assignment) {
//   CopyCounter::resetCopyCounter();
//   BoundedBuffer<CopyCounter> buffer{100}, copy{1};
//   100_times([&]() { buffer.push(CopyCounter{}); });
//   75_times([&]() { buffer.pop(); });
//   25_times([&]() { buffer.push(CopyCounter{}); });
//   copy = buffer;
//   ASSERT_EQUAL(50, CopyCounter::copy_counter);
}

auto make_suite_bounded_buffer_heap_memory_suite() -> cute::suite {
  return cute::suite{
      "BoundedBuffer Heap Memory Suite",
      {
          test_allocation_of_default_bounded_buffer,
          test_deallocation_of_default_bounded_buffer,
          test_no_undeleted_allocation_on_exception,
          test_copy_constructor_allocates_a_new_buffer,
          test_copy_self_assignment_no_additional_allocation,
          test_move_self_assignment_no_addtional_allocation,
          test_copy_only_initialized_elements_in_copy_construction,
          test_copy_only_initialized_elements_in_copy_assignment,
          test_move_constructor_does_not_allocate_a_new_buffer,
          test_copy_assignment_one_additional_allocation,
          test_move_assignment_no_additional_allocation,
      }};
}