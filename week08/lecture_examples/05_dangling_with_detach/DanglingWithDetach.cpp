#include <iostream>
#include <string>
#include <thread>

auto startThread() -> void {
  using namespace std::chrono_literals;
  std::string local{"local"};
  std::thread t{[&] {
    std::this_thread::sleep_for(1s);
    std::cout << local << std::endl;
  }};
  t.detach();
}

auto main() -> int {
  using namespace std::chrono_literals;
  startThread();
  std::this_thread::sleep_for(2s);
}
