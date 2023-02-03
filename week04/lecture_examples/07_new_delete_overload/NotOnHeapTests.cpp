#include "NotOnHeap.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

#include <cstddef>
#include <memory>
#include <new>
#include <vector>

// Allocation as local variable
TEST(test_stack_allocation_works) {
  not_on_heap const x{};
  ASSERTM("start writing tests", x.valid());
}

// Allocation as static variable
TEST(test_static_allocation_works) {
  static not_on_heap const y{};
  ASSERTM("start writing tests", y.valid());
}

// Allocation on heap with new
TEST(test_heap_allocation_throws) {
  ASSERT_THROWS(new not_on_heap{}, std::bad_alloc);
}

// Allocation in array on heap
TEST(test_heap_alloction_of_array_throws) {
  ASSERT_THROWS(new not_on_heap[2]{}, std::bad_alloc);
}

// Allocation in vector on heap
TEST(test_vector_still_works) {
  std::vector<not_on_heap> const v{3};
  ASSERT_EQUAL(3, v.size());
}

// Allocation with make_unique
TEST(test_with_make_unique) {
  ASSERT_THROWS(std::make_unique<not_on_heap>(), std::bad_alloc);
}

// Allocation as unique_ptr with new
TEST(test_create_unique_ptr_from_new) {
  ASSERT_THROWS(std::unique_ptr<not_on_heap>{new not_on_heap{}},
                std::bad_alloc);
}

// Allocation with make_shared
TEST(test_with_make_shared) {
  auto sp = std::make_shared<not_on_heap>();
  ASSERTM("should be real pointer", sp != nullptr);
  // ASSERT_THROWS(std::make_shared<not_on_heap>(), std::bad_alloc);
}

// Allocation with placement new
TEST(test_with_placement_new) {
  auto const spaceForNotOnHeap = new std::byte[sizeof(not_on_heap)]{};
  not_on_heap const* const ptr = ::new (spaceForNotOnHeap) not_on_heap{};
  ASSERT(ptr->valid());
  ptr->~not_on_heap();
  delete[] spaceForNotOnHeap;
}

auto main(int argc, char const* argv[]) -> int {
  auto suite = cute::suite{"NotOnHeap Tests",
                           {
                               test_stack_allocation_works,
                               test_heap_allocation_throws,
                               test_heap_alloction_of_array_throws,
                               test_vector_still_works,
                               test_with_make_unique,
                               test_with_make_shared,
                               test_create_unique_ptr_from_new,
                               test_static_allocation_works,
                               test_with_placement_new,
                           }};

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}
