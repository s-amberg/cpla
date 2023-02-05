// unsigned increment(unsigned i) {
//   return i++;
// }

template <typename T>
auto increment(T value) -> decltype(value.increment()) {
  return value.increment();
}

auto main() -> int {
  // return increment(42);
}
