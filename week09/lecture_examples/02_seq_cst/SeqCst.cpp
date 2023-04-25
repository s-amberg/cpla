#include <atomic>
#include <iostream>
#include <thread>

std::atomic<bool> x, y;
std::atomic<int> z;

auto write_x() -> void {
  x.store(true);
}

auto write_y() -> void {
  y.store(true);
}

auto read_x_then_y() -> void {
  while (!x.load())
    ;
  if (y.load())
    ++z;
}

auto read_y_then_x() -> void {
  while (!y.load())
    ;
  if (x.load())
    ++z;
}

auto main() -> int {
  x = false;
  y = false;
  z = 0;
  auto a = std::thread(write_x);
  auto c = std::thread(read_x_then_y);
  auto b = std::thread(write_y);
  auto d = std::thread(read_y_then_x);
  a.join();
  b.join();
  c.join();
  d.join();
  std::cout << "z == " << z << '\n';
}
