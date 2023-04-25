#include <atomic>
#include <iostream>
#include <thread>

std::atomic<bool> x, y;
std::atomic<int> z;

auto write_x() -> void {
  x.store(true, std::memory_order_release);
}

auto write_y() -> void {
  y.store(true, std::memory_order_release);
}

auto read_x_then_y() -> void {
  while (!x.load(std::memory_order_acquire))
    ;
  if (y.load(std::memory_order_acquire))
    ++z;
}

auto read_y_then_x() -> void {
  while (!y.load(std::memory_order_acquire))
    ;
  if (x.load(std::memory_order_acquire))
    ++z;
}

auto main() -> int {
  x = false;
  y = false;
  z = 0;
  auto c = std::thread(read_x_then_y);
  auto d = std::thread(read_y_then_x);
  auto a = std::thread(write_x);
  auto b = std::thread(write_y);
  a.join();
  b.join();
  c.join();
  d.join();
  std::cout << "z == " << z << '\n';
}
