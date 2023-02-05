auto increment(unsigned i) -> unsigned {
  return i++;
}

template <typename T>
auto increment(T value) -> T {
  return value.increment();
}

auto main() -> int {
  // return increment(42);
}
