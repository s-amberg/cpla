// !! CONTENT IS THE SAME AS THE PREVIOUS WEEK !!

#include "BoundedBufferSignaturesSuite.hpp"
#include "BoundedBuffer.hpp"

#include <array>

#include <boost/type_index.hpp>

#include <cute/cute.h>


TEST(test_bounded_buffer_value_type_is_value) {
  //	auto value_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::value_type>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<int>();
  //	ASSERT_EQUAL(expected_type.pretty_name(), value_type.pretty_name());
}

TEST(test_bounded_buffer_reference_type_is_reference) {
  //	auto reference_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::reference>();
  //	auto expected_type = boost::typeindex::type_id_with_cvr<int &>();
  //	ASSERT_EQUAL(expected_type.pretty_name(), reference_type.pretty_name());
}

TEST(test_bounded_buffer_const_reference_type_is_const_reference) {
  //	auto const_reference_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::const_reference>();
  // 	auto expected_type = boost::typeindex::type_id_with_cvr<int const &>();
  //	ASSERT_EQUAL(expected_type.pretty_name(), const_reference_type.pretty_name());
}

TEST(test_bounded_buffer_container_type_is_array) {
  //	auto container_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::container_type>();
  // 	auto expected_type = boost::typeindex::type_id_with_cvr<std::array<int, 15>>();
  //	ASSERT_EQUAL(expected_type.pretty_name(), container_type.pretty_name());
}

TEST(test_bounded_buffer_size_type_is_size_t) {
  //	auto size_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::size_type>();
  // 	auto expected_type = boost::typeindex::type_id_with_cvr<size_t>();
  //	ASSERT_EQUAL(expected_type.pretty_name(), size_type.pretty_name());
}

TEST(test_const_bounded_buffer_type_of_empty_is_bool) {
  //	BoundedBuffer<int, 15> const buffer{};
  //	auto empty_type = boost::typeindex::type_id_with_cvr<decltype(buffer.empty())>();
  // 	auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
  //	ASSERT_EQUAL(expected_type.pretty_name(), empty_type.pretty_name());
}

TEST(test_const_bounded_buffer_type_of_full_is_bool) {
  //	BoundedBuffer<int, 15> const buffer{};
  //	auto full_type = boost::typeindex::type_id_with_cvr<decltype(buffer.full())>();
  // 	auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
  //	ASSERT_EQUAL(expected_type.pretty_name(), full_type.pretty_name());
}

TEST(test_bounded_buffer_front_type_is_reference_type) {
  //	BoundedBuffer<int, 15> buffer{};
  //	auto front_type = boost::typeindex::type_id_with_cvr<decltype(buffer.front())>();
  // 	auto expected_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::reference>();
  // 	ASSERT_EQUAL(expected_type.pretty_name(), front_type.pretty_name());
}

TEST(test_const_bounded_buffer_front_type_is_const_reference_type) {
  //	BoundedBuffer<int, 15> const buffer{};
  //	auto front_type = boost::typeindex::type_id_with_cvr<decltype(buffer.front())>();
  // 	auto expected_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::const_reference>();
  // 	ASSERT_EQUAL(expected_type.pretty_name(), front_type.pretty_name());
}

TEST(test_bounded_buffer_back_type_is_reference_type) {
  //	BoundedBuffer<int, 15> buffer{};
  //	auto back_type = boost::typeindex::type_id_with_cvr<decltype(buffer.back())>();
  // 	auto expected_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::reference>();
  // 	ASSERT_EQUAL(expected_type.pretty_name(), back_type.pretty_name());
}

TEST(test_const_bounded_buffer_back_type_is_const_reference_type) {
  //	BoundedBuffer<int, 15> const buffer{};
  //	auto back_type = boost::typeindex::type_id_with_cvr<decltype(buffer.back())>();
  // 	auto expected_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int, 15>::const_reference>();
  // 	ASSERT_EQUAL(expected_type.pretty_name(), back_type.pretty_name());
}

TEST(test_const_bounded_buffer_type_of_size_is_size_t) {
  //	BoundedBuffer<int, 15> const buffer{};
  //	auto size_type = boost::typeindex::type_id_with_cvr<decltype(buffer.size())>();
  // 	auto expected_type = boost::typeindex::type_id_with_cvr<size_t>();
  //	ASSERT_EQUAL(expected_type.pretty_name(), size_type.pretty_name());
}

TEST(test_bounded_buffer_type_of_push_of_const_lvalue_is_void) {
  //	BoundedBuffer<int, 15> buffer{};
  //	int const lvalue{23};
  //	auto push_type = boost::typeindex::type_id_with_cvr<decltype(buffer.push(lvalue))>();
  //  auto expected_type = boost::typeindex::type_id_with_cvr<void>();
  //	ASSERT_EQUAL(expected_type.pretty_name(), push_type.pretty_name());
}

TEST(test_bounded_buffer_type_of_push_of_rvalue_is_void) {
  //	BoundedBuffer<int, 15> buffer{};
  //	auto push_type = boost::typeindex::type_id_with_cvr<decltype(buffer.push(23))>();
  // 	auto expected_type = boost::typeindex::type_id_with_cvr<void>();
  //	ASSERT_EQUAL(expected_type.pretty_name(), push_type.pretty_name());
}

TEST(test_bounded_buffer_type_of_pop_is_void) {
  //	BoundedBuffer<int, 15> buffer{};
  //	auto pop_type = boost::typeindex::type_id_with_cvr<decltype(buffer.pop())>();
  // 	auto expected_type = boost::typeindex::type_id_with_cvr<void>();
  //	ASSERT_EQUAL(expected_type.pretty_name(), pop_type.pretty_name());
}

TEST(test_bounded_buffer_type_of_swap_is_void) {
  //	BoundedBuffer<int, 15> buffer{};
  //	BoundedBuffer<int, 15> other_buffer{};
  //	auto swap_type = boost::typeindex::type_id_with_cvr<decltype(buffer.swap(other_buffer))>();
  //	auto expected_type = boost::typeindex::type_id_with_cvr<void>();
  //	ASSERT_EQUAL(expected_type.pretty_name(), swap_type.pretty_name());
}

auto make_suite_bounded_buffer_signatures_suite() -> cute::suite {
  return cute::suite{
      "BoundedBuffer Signatures Suite",
      {
          test_bounded_buffer_value_type_is_value,
          test_bounded_buffer_reference_type_is_reference,
          test_bounded_buffer_container_type_is_array,
          test_bounded_buffer_const_reference_type_is_const_reference,
          test_bounded_buffer_size_type_is_size_t,
          test_const_bounded_buffer_type_of_empty_is_bool,
          test_const_bounded_buffer_type_of_full_is_bool,
          test_bounded_buffer_front_type_is_reference_type,
          test_bounded_buffer_back_type_is_reference_type,
          test_const_bounded_buffer_back_type_is_const_reference_type,
          test_const_bounded_buffer_front_type_is_const_reference_type,
          test_const_bounded_buffer_type_of_size_is_size_t,
          test_bounded_buffer_type_of_push_of_const_lvalue_is_void,
          test_bounded_buffer_type_of_push_of_rvalue_is_void,
          test_bounded_buffer_type_of_pop_is_void,
          test_bounded_buffer_type_of_swap_is_void,
      }};
}
