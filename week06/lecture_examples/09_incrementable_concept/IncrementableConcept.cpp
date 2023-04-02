#include <concepts>
#include <iostream>
#include <type_traits>
#include <utility>

auto increment(unsigned i) -> unsigned {
  std::cout << "increment(unsinged i) selected\n";
  return i++;
}

//different from std::incrementable
template <typename T>
concept Incrementable = requires (T const v){
  {v.increment()} -> std::same_as<T>;
};

// template <Incrementable T>
// auto increment(T value) -> T {
//   std::cout << "increment(T value) selected\n";
//   return value.increment();
// }

// auto increment(Incrementable auto value) -> decltype(value) {
//   std::cout << "increment(T value) selected\n";
//   return value.increment();
// }

// template <typename T>
// requires Incrementable<T>
// auto increment(T value) -> T {
//   std::cout << "increment(T value) selected\n";
//   return value.increment();
// }

// template <typename T>
// auto increment(T value) -> T requires Incrementable<T> {
//   std::cout << "increment(T value) selected\n";
//   return value.increment();
// }

// template <typename T>
// requires requires (T const v){ {v.increment()} -> std::same_as<T>; }
// auto increment(T value) -> T {
//   std::cout << "increment(T value) selected\n";
//   return value.increment();
// }

template <typename T>
auto increment(T value) -> T requires requires (T const v){ {v.increment()} -> std::same_as<T>; } {
  std::cout << "increment(T value) selected\n";
  return value.increment();
}

struct Interval
{
  [[nodiscard]] auto increment() const -> Interval
  {
    return {start, end + 1};
  }

  unsigned start;
  unsigned end;
};

auto main() -> int {
  increment(42);
  
  Interval interval{0, 10};
  increment(interval);
}

