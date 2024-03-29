#include <cstddef>
#include <iostream>
#include <memory>

struct Point {
  Point(int x, int y) : x{x}, y{y} {
    std::cout << "creating Point{" << x << ", " << y << "}\n";
  }
  ~Point() { std::cout << "destroying Point{" << x << ", " << y << "}\n"; }

  int x, y;
};

auto elementAt(std::byte* memory, size_t index) -> Point& {
  return reinterpret_cast<Point*>(memory)[index];
}

auto main() -> int {
  //	new Point[2];
  auto memory = std::make_unique<std::byte[]>(sizeof(Point[2]));
  Point* first = &elementAt(memory.get(), 0);
  new (first) Point{1, 2};
  Point* second = &elementAt(memory.get(), 1);
  new (second) Point{4, 5};

  std::destroy_at(second);
  std::destroy_at(first);
  //	second->~Point();
  //	first->~Point();
}
