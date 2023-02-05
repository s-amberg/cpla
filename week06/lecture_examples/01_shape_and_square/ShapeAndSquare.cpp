#include <iostream>

struct Shape {
  [[nodiscard]] virtual auto area() const -> unsigned = 0;
  virtual ~Shape() = default;
};

struct Square : Shape {
  explicit Square(unsigned side_length) : side_length{side_length} {}
  [[nodiscard]] auto area() const -> unsigned override { return side_length * side_length; }
  unsigned const side_length;
};

auto main(int argc, char** argv) -> int {
  // 1 for non-virtual (empty) Shape
  // 4 or 8 for virtual (empty) Shape
  std::cout << sizeof(Shape) << '\n';

  // 4 or 8 for non-virtual Square
  // 8 to 16 for virtual Square
  std::cout << sizeof(Square) << '\n';
}
