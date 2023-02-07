#include "Vector.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

#include <sstream>

TEST(testCreateVectorWithSingleElement) {
  //	constexpr Vector<double, 1> v{1.0};
  //	static_assert(v[0] == 1.0);
  //	ASSERT_EQUAL(1.0, v[0]);
}

TEST(testCreateVectorWithTwoElements) {
  //	constexpr Vector<double, 2> v{1.0, 2.0};
  //	static_assert(v[0] == 1.0);
  //	static_assert(v[1] == 2.0);
  //	ASSERT_EQUAL(1.0, v[0]);
  //	ASSERT_EQUAL(2.0, v[1]);
}

TEST(testCreateVectorWithoutElements) {
  //	constexpr Vector<double, 0> v{};
  //	ASSERT(true);
}

TEST(testAccessOutOfBoundsThrows) {
  //	constexpr Vector<double, 1> v{1.0};
  ////	static_assert(v[1] == 0.0);
  //	ASSERT_THROWS(v[1], std::out_of_range);
}

TEST(testDeduceTemplateArguments) {
  //	constexpr Vector v{1.0, 2.0};
  //	static_assert(v[0] == 1.0);
  //	static_assert(v[1] == 2.0);
  //	ASSERT_EQUAL(1.0, v[0]);
  //	ASSERT_EQUAL(2.0, v[1]);
}

constexpr auto create() {
  //	Vector v{1.0, 2.0};
  //	v[0] = 3.0;
  //	return v;
}

TEST(testAllowModificationOfNonConstElement) {
  //	constexpr auto v = create();
  //	static_assert(v[0] == 3.0);
  //	static_assert(v[1] == 2.0);
  //	ASSERT_EQUAL(3.0, v[0]);
  //	ASSERT_EQUAL(2.0, v[1]);
}

TEST(testCalculateLengthOfZeroVector) {
  //	constexpr Vector v{0.0, 0.0, 0.0, 0.0};
  //	constexpr auto length = v.length();
  //	static_assert(length == 0.0);
  //	ASSERT_EQUAL(0.0, length);
}

TEST(testCalculateLength) {
  //	constexpr Vector v{1.0, 2.0, 3.0};
  //	constexpr auto length = v.length();
  //	static_assert(length == std::sqrt(14.0));
  //	ASSERT_EQUAL(std::sqrt(14.0), length);
}

TEST(testCalculateLengthOfUnitVector) {
  //	constexpr Vector v{1.0 / std::sqrt(14.0), 2.0 / std::sqrt(14.0), 3.0 /
  //std::sqrt(14.0)}; 	constexpr auto length = v.length(); 	static_assert(length
  //== 1.0); 	ASSERT_EQUAL(1.0, length);
}

TEST(testEqualityComparison) {
  //	constexpr Vector v{1.0, 2.5, 3.2};
  //	static_assert(v == v);
  //	ASSERT_EQUAL(v, v);
}

TEST(testUnequalityComparision) {
  //	constexpr Vector lhs{1.0, 2.5, 3.3};
  //	constexpr Vector rhs{1.0, 2.5, 3.1};
  //	static_assert(lhs != rhs);
  //	ASSERT_NOT_EQUAL_TO(lhs, rhs);
}

TEST(testOutputOperator) {
  //	constexpr Vector v{1.1, 2.5, 3.3};
  //	std::ostringstream out { };
  //	out << v;
  //	ASSERT_EQUAL("(1.1, 2.5, 3.3)", out.str());
}

TEST(testScalarProduct) {
  //	constexpr Vector lhs{1.0, 2.0, 3.0, 4.0};
  //	constexpr Vector rhs{4.2, 1.1, 0.0, 9.5};
  //	constexpr double expected = 44.4;
  //	static_assert(lhs.scalarProduct(rhs) == expected);
  //	ASSERT_EQUAL(expected, lhs.scalarProduct(rhs));
}

auto main(int argc, char const* argv[]) -> int {
  auto suite = cute::suite{"Vector Tests",
                           {
                               testCreateVectorWithSingleElement,
                               testCreateVectorWithTwoElements,
                               testCreateVectorWithoutElements,
                               testAccessOutOfBoundsThrows,
                               testDeduceTemplateArguments,
                               testAllowModificationOfNonConstElement,
                               testCalculateLengthOfZeroVector,
                               testCalculateLength,
                               testCalculateLengthOfUnitVector,
                               testEqualityComparison,
                               testUnequalityComparision,
                               testOutputOperator,
                               testScalarProduct,
                           }};

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}