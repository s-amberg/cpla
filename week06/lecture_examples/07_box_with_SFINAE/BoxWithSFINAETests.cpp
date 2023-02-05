#include "MemoryOperationCounter.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

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

TEST(testCopyBox) {
  MemoryOperationCounter const expected{1, 1, true};
  Box<MemoryOperationCounter> b{};
  b.emplace(MemoryOperationCounter{});
  auto copy = b;
  ASSERT_EQUAL(expected, copy.front());
}

TEST(testCopyConstBox) {
  MemoryOperationCounter const expected{1, 1, true};
  Box<MemoryOperationCounter> b{};
  b.emplace(MemoryOperationCounter{});
  Box<MemoryOperationCounter> const& bRef = b;
  auto copy = bRef;
  ASSERT_EQUAL(expected, copy.front());
}

TEST(testMoveBox) {
  MemoryOperationCounter const expected{1, 0, true};
  Box<MemoryOperationCounter> b{};
  b.emplace(MemoryOperationCounter{});
  auto copy = std::move(b);
  ASSERT_EQUAL(expected, copy.front());
}

TEST(testSizeCtor) {
  MemoryOperationCounter const expected{0, 0, true};
  Box<MemoryOperationCounter> b{1};
  ASSERT_EQUAL(expected, b.front());
}

auto main(int argc, char const* argv[]) -> int {
  auto suite = cute::suite{"Box with SFINAE Tests",
                           {
                               testCopyBox,
                               testMoveBox,
                               testCopyConstBox,
                               testSizeCtor,
                           }};

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}
