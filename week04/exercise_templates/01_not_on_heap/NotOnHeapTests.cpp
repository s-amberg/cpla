#include "NotOnHeap.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <memory>
#include <new>
#include <algorithm>


// Allocation as local variable
TEST_CASE("Stack Allocation Works", "NotOnHeap Suite") {
    not_on_heap noh{};
    REQUIRE(noh.valid());

}

// cannot call new
TEST_CASE("cannot call new", "NotOnHeap Suite") {
    not_on_heap noh;
    REQUIRE_THROWS_AS(new not_on_heap{}, std::bad_alloc);
}

// cannot call new[]
TEST_CASE("cannot call new[]", "NotOnHeap Suite") {
    not_on_heap noh;
    REQUIRE_THROWS_AS(new not_on_heap[1]{not_on_heap{}}, std::bad_alloc);
}

// can use std::vector<T>
TEST_CASE("can use std::vector<T>", "NotOnHeap Suite") {
    std::vector<not_on_heap> nohs{not_on_heap{}};
    REQUIRE(std::ranges::all_of(nohs, [](auto noh){return noh.valid();}));
}

// can use makeunique
TEST_CASE("can use makeunique", "NotOnHeap Suite") {
    REQUIRE_THROWS(std::make_unique<not_on_heap>(not_on_heap{}));
}

// can use makeunique
TEST_CASE("can use uniqueptr", "NotOnHeap Suite") {
    std::unique_ptr<not_on_heap> noh{};
    REQUIRE(noh->valid());
}

// can use makeunique
TEST_CASE("can use uniqueptr with new", "NotOnHeap Suite") {
    REQUIRE_THROWS(std::unique_ptr<not_on_heap>{new not_on_heap{}});
}

// can use makeshared
TEST_CASE("can use makeshared with new", "NotOnHeap Suite") {
    auto sp = std::make_shared<not_on_heap>();
    REQUIRE(sp != nullptr);

    REQUIRE_THROWS(std::unique_ptr<not_on_heap>{new not_on_heap{}});
}

TEST_CASE("Placement New Works", "[NotOnHeap Suite]") {
  auto const spaceForNotOnHeap = new std::byte[sizeof(not_on_heap)]{};
  not_on_heap const* const ptr = ::new (spaceForNotOnHeap) not_on_heap{};
  REQUIRE(ptr->valid());
  ptr->~not_on_heap();
  delete[] spaceForNotOnHeap;
}
