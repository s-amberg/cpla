#include <iostream>

struct Point {
  Point(int x, int y) : x{x}, y{y} {
    std::cout << "creating Point{" << x << ", " << y << "}\n";
  }
  int const x, y;
  ~Point() { std::cout << "destroying Point{" << x << ", " << y << "}\n"; }
};

auto createPoint(int x, int y) -> Point* {
  return new Point{x, y};  // constructor
}

auto createCorners(int x, int y) -> Point* {
  return new Point[2]{{0, 0}, {x, y}};
}

auto main(int argc, char** argv) -> int {
  auto pointPointer = createPoint(1, 2);
  auto sameLocationAnyway = new (pointPointer) Point{3, 4};
  std::cout << "pointerPointer: " << pointPointer
            << " sameLocationAnyway: " << sameLocationAnyway << "\n";
  delete pointPointer;

  std::cout << "---\n";

  auto corners = createCorners(5, 5);
  auto arrayPointerToo = new (corners) Point[2]{{15, 15}, {16, 16}};
  std::cout << "corners: " << corners << " arrayPointerToo: " << arrayPointerToo
            << "\n";
  delete[] corners;

  std::cout << "---\n";
}
