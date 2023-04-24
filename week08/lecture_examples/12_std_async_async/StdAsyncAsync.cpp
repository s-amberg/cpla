#include <future>
#include <iostream>

auto main() -> int {
  auto the_answer = std::async(std::launch::async, [] {
    // Calculate for 7.5 million years
    return 42;
  });
  std::cout << "The answer is: " << the_answer.get() << '\n';
}
