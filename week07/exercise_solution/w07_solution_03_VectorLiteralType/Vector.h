#ifndef VECTOR_H_
#define VECTOR_H_

#include <array>
#include <cmath>
#include <cstddef>
#include <type_traits>
#include <utility>
#include <ostream>

template<typename T, typename ...U>
constexpr bool are_all_same = std::conjunction_v<std::is_same<T, std::remove_cv_t<std::remove_reference_t<U>>>...>;

//From https://stackoverflow.com/questions/8622256/in-c11-is-sqrt-defined-as-constexpr
template <typename T>
constexpr T sqrt_helper(T x, T lo, T hi, unsigned depth = 0)
{
  if (depth > 100)
	return lo;
  if (lo == hi)
    return lo;

  const T mid = (lo + hi + 1) / 2;

  if (x / mid < mid)
    return sqrt_helper<T>(x, lo, mid - 1, depth + 1);
  else
    return sqrt_helper(x, mid, hi, depth + 1);
}

//From https://stackoverflow.com/questions/8622256/in-c11-is-sqrt-defined-as-constexpr
template <typename T>
constexpr T ct_sqrt(T x)
{
  return sqrt_helper<T>(x, 0, x / 2 + 1);
}

template<typename T, std::size_t N>
class Vector {
	std::array<T, N> values { };
public:
	template<typename ...U, typename = std::enable_if_t<are_all_same<T, U...>>>
	explicit constexpr Vector(U &&... u) :
			values { std::forward<U>(u)... } {
	}

	constexpr T const & operator[](size_t index) const {
		return values.at(index);
	}

	constexpr T & operator[](size_t index) {
		return values.at(index);
	}

	constexpr T length() const {
		T sum{};
		for (auto index = 0u; index < N; index++) {
			sum += values[index] * values[index];
		}
		return ct_sqrt(sum);
	}

	constexpr T scalarProduct(Vector const & other) const {
		T sum{};
		for (auto index = 0u; index < N; index++) {
			sum += values[index] * other[index];
		}
		return sum;
	}

	constexpr bool operator==(Vector const & other) const {
		for (size_t index = 0u; index < N; index++) {
			if ((*this)[index] != other[index]) {
				return false;
			}
		}
		return true;
	}

	constexpr bool operator!=(Vector const & other) const {
		return !(*this == other);
	}
};

template <typename T, std::size_t N>
std::ostream & operator<<(std::ostream & out, Vector<T, N> const & v) {
	out << '(';
	for (size_t index = 0u; index < N; index++) {
		if (index > 0u) {
			out << ", ";
		}
		out << v[index];
	}
	out << ')';
	return out;
}


template <typename Head, typename...U>
Vector(Head, U ...) -> Vector<Head, sizeof...(U) + 1>;

#endif /* VECTOR_H_ */
