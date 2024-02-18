#include "NotOnHeap.hpp"

#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <memory>
#include <new>
#include <vector>

TEST_CASE("Stack Allocation Works", "[NotOnHeap Suite]") {
  not_on_heap const x{};
  REQUIRE(x.valid());
}

TEST_CASE("Static Allocation Works", "[NotOnHeap Suite]") {
  static not_on_heap const y{};
  REQUIRE(y.valid());
}

TEST_CASE("Heap Allocation Works", "[NotOnHeap Suite]") {
  REQUIRE_THROWS_AS(new not_on_heap{}, std::bad_alloc);
}

TEST_CASE("Heap Allocation of Array Throws", "[NotOnHeap Suite]") {
  REQUIRE_THROWS_AS(new not_on_heap[2]{}, std::bad_alloc);
}

TEST_CASE("Vector Still Works", "[NotOnHeap Suite]") {
  std::vector<not_on_heap> const v{3};
  REQUIRE(v.size() == 3);
}

TEST_CASE("make_unique Throws", "[NotOnHeap Suite]") {
  REQUIRE_THROWS_AS(std::make_unique<not_on_heap>(), std::bad_alloc);
}

TEST_CASE("Create unique_ptr from new Throws", "[NotOnHeap Suite]") {
  REQUIRE_THROWS_AS(std::unique_ptr<not_on_heap>{new not_on_heap{}}, std::bad_alloc);
}

TEST_CASE("make_shared Works", "[NotOnHeap Suite]") {
  auto sp = std::make_shared<not_on_heap>();
  REQUIRE(sp != nullptr);
  // REQUIRE_THROWS_AS(std::make_shared<not_on_heap>(), std::bad_alloc);
}

TEST_CASE("Placement New Works", "[NotOnHeap Suite]") {
  auto const spaceForNotOnHeap = new std::byte[sizeof(not_on_heap)]{};
  not_on_heap const* const ptr = ::new (spaceForNotOnHeap) not_on_heap{};
  REQUIRE(ptr->valid());
  ptr->~not_on_heap();
  delete[] spaceForNotOnHeap;
}

