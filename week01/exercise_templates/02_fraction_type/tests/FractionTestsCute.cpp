#include "Fraction.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

#include <sstream>

TEST(testDefaultValueIsZero) {
	// ASSERT_EQUAL(Fraction { 0 }, Fraction { });
}

TEST(testSameFractionIsEqual) {
	// ASSERT_EQUAL(Fraction { 1 }, Fraction { 1 });
}

TEST(testDifferentFractionIsNotEqual) {
	// ASSERT_NOT_EQUAL_TO(Fraction { 1 }, Fraction { 2 });
}

TEST(testSameFractionWithDifferentDenominatorIsEqual) {
	// ASSERT_EQUAL((Fraction { 1, 2 }), (Fraction { 2, 4 }));
}

TEST(testUnaryMinus) {
	// ASSERT_EQUAL((Fraction { -15, 23 }), (-Fraction { 15, 23 }));
}

TEST(testUnaryPlus) {
	// ASSERT_EQUAL((Fraction { 15, 23 }), (+Fraction { 15, 23 }));
}

TEST(testPrintFraction) {
	// std::ostringstream out { };
	// Fraction const f { 1, 2 };
	// out << f;
	// ASSERT_EQUAL("1/2", out.str());
}

TEST(testReadFraction) {
	// Fraction expected { 6, 5 };
	// std::istringstream input { "30/25" };
	// Fraction value { };
	// input >> value;
	// ASSERT_EQUAL(expected, value);
}

TEST(testAddAssignFractions) {
	// Fraction const expected { 3, 4 };
	// Fraction result { 1, 2 };
	// Fraction const quarter { 1, 4 };
	// result += quarter;
	// ASSERT_EQUAL(expected, result);
}

TEST(testAddFractions) {
	// Fraction const expected { 3, 4 };
	// Fraction const half { 1, 2 };
	// Fraction const quarter { 1, 4 };
	// ASSERT_EQUAL(expected, half + quarter);
}

TEST(testAddAssignReduces) {
	// Fraction const expected { 3, 2 };
	// Fraction result { 3, 4 };
	// result += result;
	// ASSERT_EQUAL(expected, result);
}

TEST(testSubstractAssignFractions) {
	// Fraction const expected { 1, 5 };
	// Fraction result { 3, 5 };
	// Fraction const half { 2, 5 };
	// result -= half;
	// ASSERT_EQUAL(expected, result);
}

TEST(testSubstractFractions) {
	// Fraction const expected { 7, 10 };
	// Fraction const one { 1 };
	// Fraction const three_tenth { 3, 10 };
	// ASSERT_EQUAL(expected, one - three_tenth);
}

TEST(testSubtractAssignReduces) {
	// Fraction const expected { 1, 5 };
	// Fraction result { 7, 10 };
	// Fraction const half { 1, 2 };
	// result -= half;
	// ASSERT_EQUAL(expected, result);
}

TEST(testMultAssignFractions) {
	// Fraction const expected { 7, 15 };
	// Fraction result { 7, 5 };
	// Fraction const third { 1, 3 };
	// result *= third;
	// ASSERT_EQUAL(expected, result);
}

TEST(testMultFractions) {
	// Fraction const expected { 2, 9 };
	// Fraction const third { 1, 3 };
	// Fraction const two_thirds { 2, 3 };
	// ASSERT_EQUAL(expected, third * two_thirds);
}

TEST(testMultAssignReduces) {
	// Fraction const expected { 1, 2 };
	// Fraction result { 3, 4 };
	// Fraction const two_thirds { 2, 3 };
	// result *= two_thirds;
	// ASSERT_EQUAL(expected, result);
}

TEST(testDivAssignFractions) {
	// Fraction const expected { 21, 10 };
	// Fraction result { 7, 5 };
	// Fraction const third { 2, 3 };
	// result /= third;
	// ASSERT_EQUAL(expected, result);
}

TEST(testDivFractions) {
	// Fraction const expected { 7, 15 };
	// Fraction const third { 1, 3 };
	// Fraction const five_seventh { 5, 7 };
	// ASSERT_EQUAL(expected, third / five_seventh);
}

TEST(testDivAssignReduces) {
	// Fraction const expected { 1, 2 };
	// Fraction result { 1, 3 };
	// Fraction const two_thirds { 2, 3 };
	// result /= two_thirds;
	// ASSERT_EQUAL(expected, result);
}

TEST(testLessThanFraction) {
	// Fraction const smaller { 1, 2 };
	// Fraction const bigger { 2, 3 };
	// ASSERT_LESS(smaller, bigger);
}

TEST(testLessOrEqualFractionWithSamller) {
	// Fraction const smaller { 1, 2 };
	// Fraction const bigger { 2, 3 };
	// ASSERT_LESS_EQUAL(smaller, bigger);
}

TEST(testLessOrEqualFractionWithEqual) {
	// Fraction const f { 7, 15 };
	// ASSERT_LESS_EQUAL(f, f);
}

TEST(testGreaterThan) {
	// Fraction const smaller { 1, 2 };
	// Fraction const bigger { 2, 3 };
	// ASSERT_GREATER(bigger, smaller);
}

TEST(testGreaterOrEqualFractionWithGreater) {
	// Fraction const smaller { 1, 2 };
	// Fraction const bigger { 2, 3 };
	// ASSERT_GREATER_EQUAL(bigger, smaller);
}

TEST(testGreaterOrEqualFractionWithEqual) {
	// Fraction const f { 7, 15 };
	// ASSERT_LESS_EQUAL(f, f);
}

TEST(testPrefixIncrement) {
	// Fraction const expected{8, 5};
	// Fraction result{3, 5};
	// ++result;
	// ASSERT_EQUAL(expected, result);
}

TEST(testPostfixIncrement) {
	// Fraction const expected{8, 5};
	// Fraction result{3, 5};
	// result++;
	// ASSERT_EQUAL(expected, result);
}


TEST(testPrefixDecrement) {
	// Fraction const expected{8, 5};
	// Fraction result{13, 5};
	// --result;
	// ASSERT_EQUAL(expected, result);
}

TEST(testPostfixDecrement) {
	// Fraction const expected{8, 5};
	// Fraction result{13, 5};
	// result--;
	// ASSERT_EQUAL(expected, result);
}

TEST(testNegativeNumeratorDenomiatorEquality) {
	// Fraction const expected{-13, 27};
	// Fraction const actual{13, -27};
	// ASSERT_EQUAL(expected, actual);
}





auto main(int argc, char const* argv[]) -> int {
  auto suite = cute::suite{"Fraction Suite",
                           {
	testSameFractionIsEqual,
	testDifferentFractionIsNotEqual,
	testSameFractionWithDifferentDenominatorIsEqual,
	testAddAssignFractions,
	testAddFractions,
	testAddAssignReduces,
	testPrintFraction,
	testSubstractAssignFractions,
	testSubstractFractions,
	testSubtractAssignReduces,
	testUnaryMinus,
	testUnaryPlus,
	testMultAssignFractions,
	testMultFractions,
	testMultAssignReduces,
	testDivAssignFractions,
	testDivFractions,
	testDivAssignReduces,
	testDefaultValueIsZero,
	testReadFraction,
	testLessThanFraction,
	testLessOrEqualFractionWithSamller,
	testLessOrEqualFractionWithEqual,
	testGreaterThan,
	testGreaterOrEqualFractionWithGreater,
	testGreaterOrEqualFractionWithEqual,
	testPrefixIncrement,
	testPostfixIncrement,
	testPrefixDecrement,
	testPostfixDecrement,
	testNegativeNumeratorDenomiatorEquality,
                           }};

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}