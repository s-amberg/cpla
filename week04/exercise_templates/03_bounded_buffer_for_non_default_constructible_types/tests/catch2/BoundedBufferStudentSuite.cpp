


#include <catch2/catch_test_macros.hpp>

#include "BoundedBuffer.hpp"
#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <ios>
#include <new>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "NTimes.hpp"
// TODO: Add your own tests here

TEST_CASE("Empty Test", "[Student Suite]") {}

TEST_CASE("mytest1", "[Content Suite]") {
  BoundedBuffer<std::string> buffer{5};
  buffer.push(std::string("hello"));
  REQUIRE(buffer.size() == 1);
  REQUIRE(buffer.front() == std::string("hello"));
  REQUIRE(buffer.back() == std::string("hello"));
  // REQUIRE(buffer.front_index == 0);
  // REQUIRE(buffer.max_size == 5);
  // REQUIRE(buffer.item_count == 1);
  // REQUIRE(buffer.calculate_index(1) == 1);
  // REQUIRE(buffer.calculate_index(0) == 0);
  // REQUIRE(buffer.calculate_index(buffer.front_index+1) == 1);
  // REQUIRE(buffer.push_index() == 1);
  // REQUIRE(buffer.element_at(0) == std::string("hello"));
  // REQUIRE(buffer.item_range().size() == 1);
  // REQUIRE(buffer.element_at(1) == std::string{});
  // REQUIRE(buffer.element_at(2) == std::string{});
  // REQUIRE(buffer.element_at(3) == std::string{});
  // REQUIRE(buffer.element_at(4) == std::string{});

  // buffer.front_index = 1;
  // buffer.item_count = 0;
  // REQUIRE(std::views::iota(1, 0).size() == 0);
  // REQUIRE(buffer.item_range().size() == 0);
  // REQUIRE(buffer.element_at(4) == std::string{});

  // buffer.front_index = 0;
  // buffer.item_count = 1;
  buffer.pop();
  REQUIRE(buffer.empty());
}

TEST_CASE("iota", "[Content Suite]") {
  REQUIRE(std::views::iota(0, 1).size() == 1);
  // REQUIRE(std::views::iota(75, 50).size() == 50);
}

struct Cat {
  int _feet;
  std::string name;
  Cat(int feet) : _feet(feet) {

  }
  Cat(std::string feet) : _feet(0) , name{feet} {

  }
};
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

TEST_CASE("pushmassive", "[Content Suite]") {
  BoundedBuffer<Cat> buffer{10}, copy{1};
  buffer.push(Cat{"1"});
  buffer.push(Cat{"1"});
  buffer.push(Cat{"2"});
  buffer.push(Cat{"1"});
  buffer.push(Cat{"1"});
  buffer.push(Cat{"1"});
  buffer.push(Cat{"1"});
  buffer.push(Cat{"1"});
  buffer.push(Cat{"1"});
  buffer.push(Cat{"1"});
  REQUIRE(buffer.full());
  buffer.pop();
  buffer.pop();
  buffer.push(Cat{"1"});
  REQUIRE_FALSE(buffer.full());
  REQUIRE_FALSE(buffer.empty());
  REQUIRE(buffer.size() == 9);
}

TEST_CASE("pushmassive2", "[Content Suite]") {
  BoundedBuffer<CopyCounter> buffer{10}, copy{1};
  buffer.push(CopyCounter{});
  buffer.push(CopyCounter{});
  buffer.push(CopyCounter{});
  buffer.push(CopyCounter{});
  buffer.push(CopyCounter{});
  buffer.push(CopyCounter{});
  buffer.push(CopyCounter{});
  buffer.push(CopyCounter{});
  buffer.push(CopyCounter{});
  buffer.push(CopyCounter{});
  REQUIRE(buffer.full());
  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.push(CopyCounter{});
  buffer.push(CopyCounter{});
  REQUIRE_FALSE(buffer.full());
  REQUIRE_FALSE(buffer.empty());
  REQUIRE(buffer.size() == 7);
}

