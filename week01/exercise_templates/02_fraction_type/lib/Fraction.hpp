#ifndef FRACTION_HPP_
#define FRACTION_HPP_

#include <boost/operators.hpp>
#include <compare>
#include <cstdlib>
#include <iostream>
#include <istream>
#include <numeric>
#include <ostream>

namespace fractal {


class Fraction : boost::addable<Fraction>,
                  boost::subtractable<Fraction>,
                  boost::multipliable<Fraction>,
                  boost::dividable<Fraction>,
                  boost::incrementable<Fraction>,
                  boost::decrementable<Fraction> {

    long long num;
    long long den;

    public: 

      explicit Fraction(long long const num = 0, long long const denom = 1)
        : num{num}, den{denom} {
        reduce();
    }

    [[nodiscard]] auto numerator() const -> unsigned long long {
        return this->num;
    }

    [[nodiscard]] auto denominator() const -> long long {
        return this->den;
    }


    explicit operator double(){
        return double(num/den);
    }
    auto operator-() const -> Fraction {
        return Fraction(num, -den);
    }
    auto operator+() const -> Fraction {
        return *this;
    }
    auto operator/=(const Fraction & other) -> Fraction &{
        den = den * other.num;
        num = num * other.den;
        reduce();
        return *this;
    }

    auto operator*=(const Fraction & other) -> Fraction &{
        this->num = this->num * other.num;
        this->den = this->den * other.den;
        reduce();
        return *this;
    }

    auto operator+=(const Fraction & other) -> Fraction &{
        this->num = this->num * other.den + other.num * this->den;
        this->den = other.den * this->den;
        reduce();
        return *this;
    }
    auto operator-=(const Fraction & other) -> Fraction &{
        return *this += -other;
    }

    auto operator<=>(const Fraction & other) const -> std::strong_ordering {
        if(this->num == other.num) {
            return this->den <=> other.den;
        }
        return this->num <=> other.num;
    }
    auto operator==(const Fraction & other) const -> bool {
        return (*this <=> other) == std::strong_ordering::equal;
    }

    auto operator++() -> Fraction & {
        this->num += this->den;
        reduce();
        return *this;
    }
    auto operator--() -> Fraction & {
        this->num -= abs(this->den);
        reduce();
        return *this;
    }




    private:
        auto reduce() -> void {
            if (num == 0) {
            den = 1;
            return;
            }
            int const gcd = std::gcd(num, std::abs(den));
            num /= gcd;
            den /= gcd;
            if (den < 0) {
            num = -num;
            den = -den;
            }
        }
};

    auto operator<<(std::ostream& os, Fraction const& f) -> std::ostream& {
    os << f.numerator() << "/" << f.denominator();
    return os;
    }

    auto operator>>(std::istream& is, Fraction& f) -> std::istream& {
    unsigned int numerator{};
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

}

#endif /* FRACTION_HPP_ */
