#include "BoundedBuffer.hpp"

#include "NTimes.hpp"

#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <ios>
#include <new>
#include <ostream>
#include <stdexcept>
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

TEST_CASE("Allocation of default bounded buffer", "[Heap Memory Suite]") {
  resetAllocationTrackers();
  {
    BoundedBuffer<AllocationTracker> buffer{2};
  }
  REQUIRE(AllocationTracker::allocatedArrays.size() == 1);
}

TEST_CASE("Deallocation of default bounded buffer", "[Heap Memory Suite]") {
  resetAllocationTrackers();
  {
    BoundedBuffer<AllocationTracker> buffer{2};
  }
  REQUIRE(AllocationTracker::deallocatedArrays.size() == 1);
}

TEST_CASE("No undeleted allocation on exception", "[Heap Memory Suite]") {
  resetAllocationTrackers();
  try {
    BoundedBuffer<AllocationTracker> buffer{0};
    FAIL("The tests expects the BoundedBuffer not being constructible with size 0.");
  } catch (std::invalid_argument const& e) {
    REQUIRE(AllocationTracker::deallocatedArrays == AllocationTracker::allocatedArrays);
  }
}

TEST_CASE("Copy constructor allocates a new buffer", "[Heap Memory Suite]") {
  resetAllocationTrackers();
  BoundedBuffer<AllocationTracker> buffer{15};
  BoundedBuffer<AllocationTracker> copy{buffer};
  REQUIRE(AllocationTracker::allocatedArrays.size() == 2);
}

TEST_CASE("Move constructor does not allocate a new buffer", "[Heap Memory Suite]") {
  resetAllocationTrackers();
  BoundedBuffer<AllocationTracker> buffer{15};
  BoundedBuffer<AllocationTracker> moved{std::move(buffer)};
  REQUIRE(AllocationTracker::allocatedArrays.size() == 1);
}

TEST_CASE("Copy assignment one additional allocation", "[Heap Memory Suite]") {
  resetAllocationTrackers();
  BoundedBuffer<AllocationTracker> buffer{3}, copy{2};
  buffer.push(AllocationTracker{});
  buffer.push(AllocationTracker{});
  copy = buffer;
  REQUIRE(AllocationTracker::allocatedArrays.size() == 3);
}

TEST_CASE("Move assignment no additional allocation", "[Heap Memory Suite]") {
  resetAllocationTrackers();
  BoundedBuffer<AllocationTracker> buffer{3}, move{2};
  buffer.push(AllocationTracker{});
  buffer.push(AllocationTracker{});
  move = std::move(buffer);
  REQUIRE(AllocationTracker::allocatedArrays.size() == 2);
}

TEST_CASE("Copy self-assignment no additional allocation", "[Heap Memory Suite]") {
  resetAllocationTrackers();
  BoundedBuffer<AllocationTracker> buffer{3};
  buffer.push(AllocationTracker{});
  buffer.push(AllocationTracker{});
  buffer = (buffer);
  REQUIRE(AllocationTracker::allocatedArrays.size() == 1);
}

TEST_CASE("Move self-assignment no additional allocation", "[Heap Memory Suite]") {
  resetAllocationTrackers();
  BoundedBuffer<AllocationTracker> buffer{3};
  buffer.push(AllocationTracker{});
  buffer.push(AllocationTracker{});
  buffer = std::move(buffer);
  REQUIRE(AllocationTracker::allocatedArrays.size() == 1);
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

TEST_CASE("Copy only initialized elements in copy construction", "[Heap Memory Suite]") {
  CopyCounter::resetCopyCounter();
  BoundedBuffer<CopyCounter> buffer{100};
  100_times([&]() { buffer.push(CopyCounter{}); });
  75_times([&]() { buffer.pop(); });
  25_times([&]() { buffer.push(CopyCounter{}); });
  BoundedBuffer<CopyCounter> copy{buffer};
  REQUIRE(CopyCounter::copy_counter == 50);
}

TEST_CASE("Copy only initialized elements in copy assignment", "[Heap Memory Suite]") {
  // CopyCounter::resetCopyCounter();
  // BoundedBuffer<CopyCounter> buffer{100}, copy{1};
  // 100_times([&]() { buffer.push(CopyCounter{}); });
  // 75_times([&]() { buffer.pop(); });
  // 25_times([&]() { buffer.push(CopyCounter{}); });
  // copy = buffer;
  // REQUIRE(CopyCounter::copy_counter == 50);
}