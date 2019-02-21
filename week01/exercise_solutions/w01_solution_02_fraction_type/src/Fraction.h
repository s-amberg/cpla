#ifndef FRACTION_H_
#define FRACTION_H_
#include <boost/operators.hpp>
#include <cmath>
#include <istream>
#include <numeric>
#include <ostream>

struct Fraction : 	boost::equality_comparable<Fraction>,
					boost::less_than_comparable<Fraction>,
					boost::addable<Fraction>,
					boost::subtractable<Fraction>,
					boost::multipliable<Fraction>,
					boost::dividable<Fraction>,
					boost::incrementable<Fraction>,
					boost::decrementable<Fraction> {

	explicit Fraction(long long const num = 0, long long const denom = 1) :
			num { num }, denom { denom } {
		reduce();
	}

	explicit operator double() const {
		return static_cast<double>(num) / denom;
	}

	long long numerator() const {
		return num;
	}

	long long denominator() const {
		return denom;
	}

	Fraction operator-() const {
		return Fraction{-num, denom};
	}

	Fraction operator+() const {
		return *this;
	}

	Fraction & operator+=(Fraction const & other) {
		auto const new_denominator { denom * other.denom };
		num = num * other.denom + other.num * denom ;
		denom = new_denominator;
		reduce();
		return *this;
	}

	Fraction & operator-=(Fraction const & other) {
		return (*this) += -other;
	}

	Fraction & operator*=(Fraction const & other) {
		denom = denom * other.denom;
		num = num * other.num;
		reduce();
		return *this;
	}

	Fraction & operator/=(Fraction const & other) {
		denom = denom * other.num;
		num = num * other.denom;
		reduce();
		return *this;
	}

	bool operator==(Fraction const & other) const {
		return num == other.num && denom == other.denom;
	}

	bool operator<(Fraction const & other) const {
		return num * other.denom < other.num * denom;
	}

	Fraction & operator++() {
		num += denom;
		return *this;
	}

	Fraction & operator--() {
		num -= denom;
		return *this;
	}

private:
	void reduce() {
		if (num == 0) {
			denom = 1;
			return;
		}
		int const gcd = std::gcd(std::abs(num), std::abs(denom));
		num /= gcd;
		denom /= gcd;
		if (denom < 0) {
			num = -num;
			denom =  -denom;
		}
	}

	long long num;
	long long denom;
};


std::ostream & operator<<(std::ostream & os, Fraction const & f) {
	os << f.numerator() << "/" << f.denominator();
	return os;
}

std::istream & operator>>(std::istream & is, Fraction & f) {
	int numerator { };
	char div_operator { };
	int denominator { };
	is >> numerator >> div_operator >> denominator;
	if (div_operator == '/') {
		f = Fraction{numerator, denominator};
	} else {
		is.setstate(std::ios_base::failbit);
	}
	return is;
}


#endif /* FRACTION_H_ */
