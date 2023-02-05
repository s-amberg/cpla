#include <type_traits>

auto increment(unsigned i) -> unsigned {
  return i++;
}

template<typename T>
auto increment(T value) -> std::enable_if_t<std::is_class<T>::value, T> {
  return value.increment();
}

// template<typename T>
// auto increment(std::enable_if_t<std::is_class<T>::value, T> value) -> T {
//  return value.increment();
// }

// template<typename T, typename = std::enable_if_t<std::is_class<T>::value, void>>
// auto increment(T value) -> T {
//  return value.increment();
// }


auto main() -> int {
  return increment(42);
}
