#include <array>
#include <cmath>

template <typename T>
class Vector {
	constexpr static size_t dimensions = 3;
	std::array<T, dimensions> values{};
	
public:
	constexpr Vector(T x, T y, T z)
		: values{x, y, z}{}
	constexpr T length() const {
		auto squares = x() * x() + y() * y() + z() * z();
		return std::sqrt(squares);
	}
	constexpr T & x() {
		return values[0];
	}
	constexpr T const & x() const {
		return values[0];
	}
	constexpr T & y() {
		return values[1];
	}
	constexpr T const & y() const {
		return values[1];
	}
	constexpr T & z() {
		return values[2];
	}
	constexpr T const & z() const {
		return values[2];
	}
};

constexpr bool doubleEqual(double first, double second, double epsilon = 0.0001) {
	return std::abs(first - second) < epsilon;
}

constexpr Vector<double> create() {
	Vector<double> v{1.0, 1.0, 1.0};
	v.x() = 2.0;
	return v;
}

constexpr auto v = create();
static_assert(doubleEqual(v.length(), 2.4495));

int main() {
	//v.x() = 1.0;
	auto v2 = create();
	v2.x() = 2.0;
}
