#include <atomic>
#include <cassert>
#include <thread>

std::atomic<bool> x{};
std::atomic<bool> y{};
std::atomic<int> z{};

auto write_x_then_y() -> void {
  x.store(true, std::memory_order_relaxed);
  y.store(true, std::memory_order_relaxed);
}

auto read_y_then_x() -> void {
  while (!y.load(std::memory_order_relaxed)) {
    // Spin ...
  }

  if (x.load(std::memory_order_relaxed)) {
    ++z;
  }
}

auto main() -> int {
  auto a = std::thread{write_x_then_y};
  auto b = std::thread{read_y_then_x};
  a.join();
  b.join();
  assert(z.load() != 0);
}
