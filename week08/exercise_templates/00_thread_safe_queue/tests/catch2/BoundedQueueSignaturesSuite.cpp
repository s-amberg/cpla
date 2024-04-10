// #include "BoundedQueue.hpp"

#include <boost/type_index.hpp>
#include <catch2/catch_test_macros.hpp>

#include <chrono>
#include <cstddef>

TEST_CASE("Queue value_type is value", "[Signatures Suite]") {
  // auto value_type = boost::typeindex::type_id_with_cvr<BoundedQueue<int>::value_type>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<int>();
  // REQUIRE(value_type.pretty_name() == expected_type.pretty_name());
}

TEST_CASE("Queue reference type is reference", "[Signatures Suite]") {
  // auto reference_type = boost::typeindex::type_id_with_cvr<BoundedQueue<int>::reference>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<int &>();
  // REQUIRE(reference_type.pretty_name() == expected_type.pretty_name());
}

TEST_CASE("Queue const_reference type is const reference", "[Signatures Suite]") {
  // auto const_reference_type = boost::typeindex::type_id_with_cvr<BoundedQueue<int>::const_reference>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<int const &>();
  // REQUIRE(const_reference_type.pretty_name() == expected_type.pretty_name());
}

TEST_CASE("Queue size_type is size_t", "[Signatures Suite]") {
  // auto size_type = boost::typeindex::type_id_with_cvr<BoundedQueue<int>::size_type>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<std::size_t>();
  // REQUIRE(size_type.pretty_name() == expected_type.pretty_name());
}

TEST_CASE("Queue empty type is bool", "[Signatures Suite]") {
  // BoundedQueue<int> const queue{15};
  // auto empty_type = boost::typeindex::type_id_with_cvr<decltype(queue.empty())>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
  // REQUIRE(empty_type.pretty_name() == expected_type.pretty_name());
}

TEST_CASE("Queue full type is bool", "[Signatures Suite]") {
  // BoundedQueue<int> const queue{15};
  // auto full_type = boost::typeindex::type_id_with_cvr<decltype(queue.full())>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
  // REQUIRE(full_type.pretty_name() == expected_type.pretty_name());
}

TEST_CASE("Queue size type is size_t", "[Signatures Suite]") {
  // BoundedQueue<int> const queue{15};
  // auto size_type = boost::typeindex::type_id_with_cvr<decltype(queue.size())>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<size_t>();
  // REQUIRE(size_type.pretty_name() == expected_type.pretty_name());
}

TEST_CASE("Queue type of push of const lvalue is void", "[Signatures Suite]") {
  // BoundedQueue<int> queue{15};
  // int const lvalue{23};
  // auto push_type = boost::typeindex::type_id_with_cvr<decltype(queue.push(lvalue))>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<void>();
  // REQUIRE(push_type.pretty_name() == expected_type.pretty_name());
}

TEST_CASE("Queue type of push of rvalue is void", "[Signatures Suite]") {
  // BoundedQueue<int> queue{15};
  // auto push_type = boost::typeindex::type_id_with_cvr<decltype(queue.push(23))>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<void>();
  // REQUIRE(push_type.pretty_name() == expected_type.pretty_name());
}

TEST_CASE("Queue type of try_push of const lvalue is bool", "[Signatures Suite]") {
  // BoundedQueue<int> queue{15};
  // int const lvalue{23};
  // auto push_type = boost::typeindex::type_id_with_cvr<decltype(queue.try_push(lvalue))>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
  // REQUIRE(push_type.pretty_name() == expected_type.pretty_name());
}

TEST_CASE("Queue type of try_push of rvalue is bool", "[Signatures Suite]") {
  // BoundedQueue<int> queue{15};
  // auto push_type = boost::typeindex::type_id_with_cvr<decltype(queue.try_push(23))>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
  // REQUIRE(push_type.pretty_name() == expected_type.pretty_name());
}

TEST_CASE("Queue type of pop is value_type", "[Signatures Suite]") {
  // BoundedQueue<int> queue{15};
  // auto pop_type = boost::typeindex::type_id_with_cvr<decltype(queue.pop())>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<int>();
  // REQUIRE(pop_type.pretty_name() == expected_type.pretty_name());
}

TEST_CASE("Queue type of try_pop is bool", "[Signatures Suite]") {
  // BoundedQueue<int> queue{15};
  // int popped_value{};
  // auto pop_type = boost::typeindex::type_id_with_cvr<decltype(queue.try_pop(popped_value))>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
  // REQUIRE(pop_type.pretty_name() == expected_type.pretty_name());
}

TEST_CASE("Queue type of swap is void", "[Signatures Suite]") {
  // BoundedQueue<int> queue{15}, other_queue{15};
  // auto pop_type = boost::typeindex::type_id_with_cvr<decltype(queue.swap(other_queue))>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<void>();
  // REQUIRE(pop_type.pretty_name() == expected_type.pretty_name());
}

TEST_CASE("Queue type of try_push_for is bool", "[Signatures Suite]") {
  // BoundedQueue<int> queue{15};
  // auto pop_type = boost::typeindex::type_id_with_cvr<decltype(queue.try_push_for(1, std::chrono::seconds{1}))>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
  // REQUIRE(pop_type.pretty_name() == expected_type.pretty_name());
}

TEST_CASE("Queue type of try_pop_for is bool", "[Signatures Suite]") {
  // BoundedQueue<int> queue{15};
  // int result{};
  // auto pop_type = boost::typeindex::type_id_with_cvr<decltype(queue.try_pop_for(result, std::chrono::seconds{1}))>();
  // auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
  // REQUIRE(pop_type.pretty_name() == expected_type.pretty_name());
}
