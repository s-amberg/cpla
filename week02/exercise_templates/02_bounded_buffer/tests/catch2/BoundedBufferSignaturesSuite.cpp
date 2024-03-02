
#include "BoundedBuffer.hpp"

#include <array>
#include <boost/type_index.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cstddef>

using namespace buffy;

TEST_CASE("value_type is value", "[Signatures Suite]") {
  auto value_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::value_type>();
  auto expected_type = boost::typeindex::type_id_with_cvr<int>();
  REQUIRE(expected_type.pretty_name() == value_type.pretty_name());
}

TEST_CASE("reference_type is reference", "[Signatures Suite]") {
  auto reference_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::reference>();
  auto expected_type = boost::typeindex::type_id_with_cvr<int &>();
  REQUIRE(expected_type.pretty_name() == reference_type.pretty_name());
}

TEST_CASE("const_reference_type is const reference", "[Signatures Suite]") {
  auto const_reference_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::const_reference>();
  auto expected_type = boost::typeindex::type_id_with_cvr<int const &>();
  REQUIRE(expected_type.pretty_name() == const_reference_type.pretty_name());
}

TEST_CASE("container_type is array", "[Signatures Suite]") {
  auto container_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::container_type>();
  auto expected_type = boost::typeindex::type_id_with_cvr<std::array<int, 15>>();
  REQUIRE(expected_type.pretty_name() == container_type.pretty_name());
}

TEST_CASE("size_type is std::size_t", "[Signatures Suite]") {
  auto size_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::size_type>();
  auto expected_type = boost::typeindex::type_id_with_cvr<std::size_t>();
  REQUIRE(expected_type.pretty_name() == size_type.pretty_name());
}

TEST_CASE("empty() type is bool", "[Signatures Suite]") {
  BoundedBuffer<int, 15> const buffer{};
  auto empty_type = boost::typeindex::type_id_with_cvr<decltype(buffer.empty())>();
  auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
  REQUIRE(expected_type.pretty_name() == empty_type.pretty_name());
}

TEST_CASE("full() type is bool", "[Signatures Suite]") {
  BoundedBuffer<int, 15> const buffer{};
  auto full_type = boost::typeindex::type_id_with_cvr<decltype(buffer.full())>();
  auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
  REQUIRE(expected_type.pretty_name() == full_type.pretty_name());
}

TEST_CASE("front() type is reference type", "[Signatures Suite]") {
  BoundedBuffer<int, 15> buffer{};
  auto front_type = boost::typeindex::type_id_with_cvr<decltype(buffer.front())>();
  auto expected_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::reference>();
  REQUIRE(expected_type.pretty_name() == front_type.pretty_name());
}

TEST_CASE("front() const type is const_reference type", "[Signatures Suite]") {
  BoundedBuffer<int, 15> const buffer{};
  auto front_type = boost::typeindex::type_id_with_cvr<decltype(buffer.front())>();
  auto expected_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::const_reference>();
  REQUIRE(expected_type.pretty_name() == front_type.pretty_name());
}

TEST_CASE("back() type is reference type", "[Signatures Suite]") {
  BoundedBuffer<int, 15> buffer{};
  auto front_type = boost::typeindex::type_id_with_cvr<decltype(buffer.back())>();
  auto expected_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::reference>();
  REQUIRE(expected_type.pretty_name() == front_type.pretty_name());
}

TEST_CASE("back() const type is cosnt_reference type", "[Signatures Suite]") {
  BoundedBuffer<int, 15> const buffer{};
  auto front_type = boost::typeindex::type_id_with_cvr<decltype(buffer.back())>();
  auto expected_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::const_reference>();
  REQUIRE(expected_type.pretty_name() == front_type.pretty_name());
}

TEST_CASE("size() type is size_type", "[Signatures Suite]") {
  BoundedBuffer<int, 15> const buffer{};
  auto size_type = boost::typeindex::type_id_with_cvr<decltype(buffer.size())>();
  auto expected_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::size_type>();
  REQUIRE(expected_type.pretty_name() == size_type.pretty_name());
}

TEST_CASE("push(const_lvalue) type is void", "[Signatures Suite]") {
  BoundedBuffer<int, 15> buffer{};
  int const lvalue{23};
  auto push_type = boost::typeindex::type_id_with_cvr<decltype(buffer.push(lvalue))>();
  auto expected_type = boost::typeindex::type_id_with_cvr<void>();
  REQUIRE(expected_type.pretty_name() == push_type.pretty_name());
}

TEST_CASE("push(rvalue) type is void", "[Signatures Suite]") {
  BoundedBuffer<int, 15> buffer{};
  auto push_type = boost::typeindex::type_id_with_cvr<decltype(buffer.push(23))>();
  auto expected_type = boost::typeindex::type_id_with_cvr<void>();
  REQUIRE(expected_type.pretty_name() == push_type.pretty_name());
}

TEST_CASE("pop() type is void", "[Signatures Suite]") {
  BoundedBuffer<int, 15> buffer{};
  auto pop_type = boost::typeindex::type_id_with_cvr<decltype(buffer.pop())>();
  auto expected_type = boost::typeindex::type_id_with_cvr<void>();
  REQUIRE(expected_type.pretty_name() == pop_type.pretty_name());
}

TEST_CASE("swap() type is void", "[Signatures Suite]") {
  BoundedBuffer<int, 15> buffer{};
  BoundedBuffer<int, 15> other_buffer{};
  auto swap_type = boost::typeindex::type_id_with_cvr<decltype(buffer.swap(other_buffer))>();
  auto expected_type = boost::typeindex::type_id_with_cvr<void>();
  REQUIRE(expected_type.pretty_name() == swap_type.pretty_name());
}