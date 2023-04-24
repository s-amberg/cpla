#include <algorithm>
#include <iostream>
#include <iterator>

#include <thread>

auto doSomethingElse() -> void {
  throw "surprise";
}

auto longRunningAction() -> void {
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(1s);
}

auto calcAsync() -> void {
  std::thread t{longRunningAction};
  doSomethingElse();
  t.join();
}

auto countAs(std::string_view str) -> void {
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(1s);
  auto nOfA = std::count(std::begin(str), std::end(str), 'A');
  std::cout << "A: " << nOfA;
}

auto countAsync(std::string_view input) -> void {
  std::thread t{[&] { countAs(input); }};
  t.detach();
}

auto main() -> int {
  countAsync("AAA");
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(2s);
  // calcAsync();
}
