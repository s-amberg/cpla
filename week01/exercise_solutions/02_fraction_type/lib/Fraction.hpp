#ifndef FRACTION_HPP_
#define FRACTION_HPP_

#include <boost/operators.hpp>
#include <cmath>
#include <compare>
#include <ios>
#include <istream>
#include <numeric>
#include <ostream>

struct Fraction : boost::addable<Fraction>,
                  boost::subtractable<Fraction>,
                  boost::multipliable<Fraction>,
                  boost::dividable<Fraction>,
                  boost::incrementable<Fraction>,
                  boost::decrementable<Fraction> {
  explicit Fraction(long long const num = 0, long long const denom = 1)
      : num{num}, denom{denom} {
    reduce();
  }

  explicit operator double() const { return static_cast<double>(num) / denom; }

  [[nodiscard]] auto numerator() const -> long long { return num; }

  [[nodiscard]] auto denominator() const -> long long { return denom; }

  auto operator-() const -> Fraction { return Fraction{-num, denom}; }

  auto operator+() const -> Fraction { return *this; }

  auto operator+=(Fraction const& other) -> Fraction& {
    auto const new_denominator{denom * other.denom};
    num = num * other.denom + other.num * denom;
    denom = new_denominator;
    reduce();
    return *this;
  }

  auto operator-=(Fraction const& other) -> Fraction& { return (*this) += -other; }

  auto operator*=(Fraction const& other) -> Fraction& {
    denom = denom * other.denom;
    num = num * other.num;
    reduce();
    return *this;
  }

  auto operator/=(Fraction const& other) -> Fraction& {
    denom = denom * other.num;
    num = num * other.denom;
    reduce();
    return *this;
  }

  auto operator==(Fraction const& other) const -> bool {
    return num == other.num && denom == other.denom;
  }

  auto operator<=>(Fraction const& other) const -> std::strong_ordering {
    return num * other.denom <=> other.num * denom;
  }

  auto operator++() -> Fraction& {
    num += denom;
    return *this;
  }

  auto operator--() -> Fraction& {
    num -= denom;
    return *this;
  }

 private:
  auto reduce() -> void {
    if (num == 0) {
      denom = 1;
      return;
    }
    int const gcd = std::gcd(std::abs(num), std::abs(denom));
    num /= gcd;
    denom /= gcd;
    if (denom < 0) {
      num = -num;
      denom = -denom;
    }
  }

  long long num;
  long long denom;
};

auto operator<<(std::ostream& os, Fraction const& f) -> std::ostream& {
  os << f.numerator() << "/" << f.denominator();
  return os;
}

auto operator>>(std::istream& is, Fraction& f) -> std::istream& {
  int numerator{};
  char div_operator{};
  int denominator{};
  is >> numerator >> div_operator >> denominator;
  if (div_operator == '/') {
    f = Fraction{numerator, denominator};
  } else {
    is.setstate(std::ios_base::failbit);
  }
  return is;
}

#endif /* FRACTION_HPP_ */
