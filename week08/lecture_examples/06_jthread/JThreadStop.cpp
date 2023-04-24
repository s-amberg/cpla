#include <iostream>
#include <stdexcept>
#include <thread>
#include <utility>
#include <chrono>

using namespace std::chrono_literals;

auto main() -> int {
  std::jthread t{[](std::stop_token token) {
    while (!token.stop_requested()) {
      std::this_thread::sleep_for(100ms);
    }
    std::cout << "Stop Requested" << std::endl;
  }};
  std::this_thread::sleep_for(2s);
  t.request_stop();
}
