#include "MemoryOperationCounter.hpp"

#include <catch2/catch_test_macros.hpp>

#include <type_traits>
#include <utility>
#include <vector>

template <typename T>
struct Box {
  Box() = default;
  //	Box(Box const & box)
  //	  : items{box.items}{}
  //	Box(Box && box)
  //	  : items{std::move(box.items)} {}
  template <typename BoxType,
            typename = std::enable_if_t<std::is_same_v<Box, BoxType>>>
  explicit Box(BoxType&& other) : items(std::forward<BoxType>(other).items) {}
  explicit Box(size_t size) : items(size) {}
  template <typename... Param>
  auto emplace(Param&&... params) -> void {
    items.emplace_back(std::forward<Param>(params)...);
  }
  auto front() -> T& { return items.front(); }

 private:
  std::vector<T> items{};
};




TEST_CASE("Copy Box", "[Box With SFINAE Suite]") {
  MemoryOperationCounter const expected{1, 1, true};
  Box<MemoryOperationCounter> b{};
  b.emplace(MemoryOperationCounter{});
  auto copy = b;
  REQUIRE(expected == copy.front());
}

TEST_CASE("Copy Const Box", "[Box With SFINAE Suite]") {
  MemoryOperationCounter const expected{1, 1, true};
  Box<MemoryOperationCounter> b{};
  b.emplace(MemoryOperationCounter{});
  Box<MemoryOperationCounter> const& bRef = b;
  auto copy = bRef;
  REQUIRE(expected == copy.front());
}

TEST_CASE("Move Box", "[Box With SFINAE Suite]") {
  MemoryOperationCounter const expected{1, 0, true};
  Box<MemoryOperationCounter> b{};
  b.emplace(MemoryOperationCounter{});
  auto copy = std::move(b);
  REQUIRE(expected == copy.front());
}

TEST_CASE("Size Constructor", "[Box With SFINAE Suite]") {
  MemoryOperationCounter const expected{0, 0, true};
  Box<MemoryOperationCounter> b{1};
  REQUIRE(expected == b.front());
}

