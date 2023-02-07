#include <array>
#include <cmath>

// From
// https://stackoverflow.com/questions/8622256/in-c11-is-sqrt-defined-as-constexpr
template <typename T>
constexpr auto sqrt_helper(T x, T lo, T hi, unsigned depth = 0) -> T {
  if (depth > 100)
    return lo;
  if (lo == hi)
    return lo;

  const T mid = (lo + hi + 1) / 2;

  if (x / mid < mid)
    return sqrt_helper<T>(x, lo, mid - 1, depth + 1);
  return sqrt_helper(x, mid, hi, depth + 1);
}

// From
// https://stackoverflow.com/questions/8622256/in-c11-is-sqrt-defined-as-constexpr
template <typename T>
constexpr auto ct_sqrt(T x) -> T {
  return sqrt_helper<T>(x, 0, x / 2 + 1);
}

template <typename T>
class Vector {
  constexpr static size_t dimensions = 3;
  std::array<T, dimensions> values{};

 public:
  constexpr Vector(T x, T y, T z) : values{x, y, z} {}
  [[nodiscard]] constexpr auto length() const -> T {
    auto squares = x() * x() + y() * y() + z() * z();
    return ct_sqrt(squares);
  }
  constexpr auto x() -> T& { return values[0]; }
  [[nodiscard]] constexpr auto x() const -> T const& { return values[0]; }
  constexpr auto y() -> T& { return values[1]; }
  [[nodiscard]] constexpr auto y() const -> T const& { return values[1]; }
  constexpr auto z() -> T& { return values[2]; }
  [[nodiscard]] constexpr auto z() const -> T const& { return values[2]; }
};

constexpr auto doubleEqual(double first, double second, double epsilon = 0.0001)
    -> bool {
  return std::abs(first - second) < epsilon;
}

constexpr auto create() -> Vector<double> {
  Vector<double> v{1.0, 1.0, 1.0};
  v.x() = 2.0;
  return v;
}

constexpr auto v = create();
static_assert(doubleEqual(v.length(), 2.4495));

auto main() -> int {
  // v.x() = 1.0;
  auto v2 = create();
  v2.x() = 2.0;
}
