#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <cstddef>
#include <type_traits>
#include <array>
#include <ostream>

template<typename T, typename ...U>
constexpr bool are_all_same = std::conjunction_v<std::is_same<T, std::remove_cv_t<std::remove_reference_t<U>>>...>;
// From
// https://stackoverflow.com/questions/8622256/in-c11-is-sqrt-defined-as-constexpr
template <typename T>
constexpr auto sqrt_helper(T x, T lo, T hi, unsigned depth = 0) -> T {
  if (depth > 100) {
    return lo;
  }
  if (lo == hi) {
    return lo;
  }

  const T mid = (lo + hi + 1) / 2;

  if (x / mid < mid) {
    return sqrt_helper<T>(x, lo, mid - 1, depth + 1);
  }

  return sqrt_helper(x, mid, hi, depth + 1);
}

// From
// https://stackoverflow.com/questions/8622256/in-c11-is-sqrt-defined-as-constexpr
template <typename T>
constexpr auto ct_sqrt(T x) -> T {
  return sqrt_helper<T>(x, 0, x / 2 + 1);
}

template<typename T, std::size_t N>
class Vector {

    std::array<T, N> container;
    std::size_t index = 0;


    public:

    template<typename... U>
    requires are_all_same<T, U...>
    explicit constexpr Vector(U&&... elements) : container{std::forward<U>(elements)...} {}

    constexpr auto length() const -> double {
        T sum{};
        for (auto index = 0u; index < N; index++) {
        sum += container[index] * container[index];
        }
        return ct_sqrt(sum);
    }
    
    constexpr auto operator[](std::size_t i) const -> T const & {
        return container.at(i);
    }

    constexpr auto operator[](std::size_t i) -> T & {
        return container.at(i);
    }

    constexpr auto operator==(Vector const & rhs) const -> bool{
        return container == rhs.container;
    }

    constexpr auto operator!=(Vector const & rhs) const -> bool{
        return !(*this == rhs);
    }

};

template<typename T, typename... Rest>
Vector(T, Rest...) -> Vector<T, sizeof...(Rest) + 1>;

template<typename T, std::size_t N>
auto operator<<(std::ostream & out, Vector<T, N> const & v) -> std::ostream&  {
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

#endif /* VECTOR_HPP_ */
