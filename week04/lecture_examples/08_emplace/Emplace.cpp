#include <iostream>
#include <memory>
#include <stack>

struct Point {
  Point(int x, int y) : x{x}, y{y} {
    std::cout << "creating Point{" << x << ", " << y << "}\n";
  }
  ~Point() { std::cout << "destroying Point{" << x << ", " << y << "}\n"; }
  Point(Point const&) = delete;
  Point(Point&&) = delete;

  int x, y;
};

auto main(int argc, char** argv) -> int {
  std::stack<Point> pointStack{};
  pointStack.emplace(1, 2);
}
