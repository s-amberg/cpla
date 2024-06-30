#include <atomic>
#include <iostream>
#include <thread>

using namespace std::this_thread;

auto outputWhenReady(std::atomic_flag &flag, std::ostream &out) -> void {
  while (flag.test_and_set(std::memory_order_acquire))
    yield();
  out << "Here is thread: " << get_id() << std::endl;
  flag.clear(std::memory_order_release);
}

auto main() -> int {
  // using std::cout;
  // using std::endl;
  // std::atomic_flag flag{};
  // std::jthread t{[&flag] { outputWhenReady(flag, cout); }};
  // outputWhenReady(flag, cout);
}
