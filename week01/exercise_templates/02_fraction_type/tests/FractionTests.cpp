#include "Fraction.hpp"

#include <catch2/catch_test_macros.hpp>

#include <sstream>

TEST_CASE("Default Value Is Zero") {
  // REQUIRE(Fraction{0} == Fraction{});
}

TEST_CASE("Same Fraction Is Equal") {
  // REQUIRE(Fraction{1} == Fraction{1});
}

TEST_CASE("Different Fraction Is Not Equal") {
  // REQUIRE(Fraction{1} != Fraction{2});
}

TEST_CASE("Same Fraction With Different Denominator Is Equal") {
  // REQUIRE(Fraction{1, 2} == Fraction{2, 4});
}

TEST_CASE("Unary Minus") {
  // REQUIRE(-Fraction{15, 23} == Fraction{-15, 23});
}

TEST_CASE("Unary Plus") {
  // REQUIRE(+Fraction{15, 23} == Fraction{15, 23});
}

TEST_CASE("Print Fraction") {
  // std::ostringstream out{};
  // Fraction const f{1, 2};
  // out << f;
  // REQUIRE(out.str() == "1/2");
}

TEST_CASE("Read Fraction") {
  // Fraction expected{6, 5};
  // std::istringstream input{"30/25"};
  // Fraction value{};
  // input >> value;
  // REQUIRE(expected == value);
}

TEST_CASE("Add Assign Fractions") {
  // Fraction const expected{3, 4};
  // Fraction result{1, 2};
  // Fraction const quarter{1, 4};
  // result += quarter;
  // REQUIRE(expected == result);
}

TEST_CASE("Add Fractions") {
  // Fraction const expected{3, 4};
  // Fraction const half{1, 2};
  // Fraction const quarter{1, 4};
  // REQUIRE(expected == half + quarter);
}

TEST_CASE("Add Assign Reduces") {
  // Fraction const expected{3, 2};
  // Fraction result{3, 4};
  // result += result;
  // REQUIRE(expected == result);
}

TEST_CASE("Subtract Assign Fractions") {
  // Fraction const expected{1, 5};
  // Fraction result{3, 5};
  // Fraction const half{2, 5};
  // result -= half;
  // REQUIRE(expected == result);
}

TEST_CASE("Subtract Fractions") {
  // Fraction const expected{7, 10};
  // Fraction const one{1};
  // Fraction const three_tenth{3, 10};
  // REQUIRE(expected == one - three_tenth);
}

TEST_CASE("Subtract Assign Reduces") {
  // Fraction const expected{1, 5};
  // Fraction result{7, 10};
  // Fraction const half{1, 2};
  // result -= half;
  // REQUIRE(expected == result);
}

TEST_CASE("Multiply Assign Fractions") {
  // Fraction const expected{7, 15};
  // Fraction result{7, 5};
  // Fraction const third{1, 3};
  // result *= third;
  // REQUIRE(expected == result);
}

TEST_CASE("Multiply Fractions") {
  // Fraction const expected{2, 9};
  // Fraction const third{1, 3};
  // Fraction const two_thirds{2, 3};
  // REQUIRE(expected == third * two_thirds);
}

TEST_CASE("Multiply Assign Reduces") {
  // Fraction const expected{1, 2};
  // Fraction result{3, 4};
  // Fraction const two_thirds{2, 3};
  // result *= two_thirds;
  // REQUIRE(expected == result);
}

TEST_CASE("Divide Assign Fractions") {
  // Fraction const expected{21, 10};
  // Fraction result{7, 5};
  // Fraction const third{2, 3};
  // result /= third;
  // REQUIRE(expected == result);
}

TEST_CASE("Divide Fractions") {
  // Fraction const expected{7, 15};
  // Fraction const third{1, 3};
  // Fraction const five_seventh{5, 7};
  // REQUIRE(expected == third / five_seventh);
}

TEST_CASE("Divide Assign Reduces") {
  // Fraction const expected{1, 2};
  // Fraction result{1, 3};
  // Fraction const two_thirds{2, 3};
  // result /= two_thirds;
  // REQUIRE(expected == result);
}

TEST_CASE("Less Than Fraction") {
  // Fraction const smaller{1, 2};
  // Fraction const bigger{2, 3};
  // REQUIRE(smaller < bigger);
}

TEST_CASE("Less Or Equal Fraction With Smaller") {
  // Fraction const smaller{1, 2};
  // Fraction const bigger{2, 3};
  // REQUIRE(smaller <= bigger);
}

TEST_CASE("Less Or Equal Fraction With Equal") {
  // Fraction const f{7, 15};
  // REQUIRE(f <= f);
}

TEST_CASE("Greater Than") {
  // Fraction const smaller{1, 2};
  // Fraction const bigger{2, 3};
  // REQUIRE(bigger > smaller);
}

TEST_CASE("Greater Or Equal Fraction With Greater") {
  // Fraction const smaller{1, 2};
  // Fraction const bigger{2, 3};
  // REQUIRE(bigger >= smaller);
}

TEST_CASE("Greater Or Equal Fraction With Equal") {
  // Fraction const f{7, 15};
  // REQUIRE(f >= f);
}

TEST_CASE("Prefix Increment") {
  // Fraction const expected{8, 5};
  // Fraction result{3, 5};
  // ++result;
  // REQUIRE(expected == result);
}

TEST_CASE("Postfix Increment") {
  // Fraction const expected{8, 5};
  // Fraction result{3, 5};
  // result++;
  // REQUIRE(expected == result);
}

TEST_CASE("Prefix Decrement") {
  // Fraction const expected{8, 5};
  // Fraction result{13, 5};
  // --result;
  // REQUIRE(expected == result);
}

TEST_CASE("Postfix Decrement") {
  // Fraction const expected{8, 5};
  // Fraction result{13, 5};
  // result--;
  // REQUIRE(expected == result);
}

TEST_CASE("Negative Numerator Denominator Equality") {
  // Fraction const expected{-13, 27};
  // Fraction const actual{13, -27};
  // REQUIRE(expected == actual);
}
