#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

auto main() -> int {
  using namespace std::chrono_literals;

  auto mutex = std::mutex{};
  auto finished = std::condition_variable{};
  auto shared = 0;

  auto thread = std::thread{[&] {
    std::this_thread::sleep_for(2s);
    auto guard = std::lock_guard{mutex};
    shared = 42;
    finished.notify_all();
  }};

  std::this_thread::sleep_for(1s);
  auto lock = std::unique_lock{mutex};
  finished.wait(lock);

  std::cout << "The answer is: " << shared << '\n';

  thread.join();
}
