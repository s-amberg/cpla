#include <boost/type_index.hpp>
#include <iostream>
#include <utility>


struct S {
  S() = default;
  S(S const&) { std::cout << "S(S const &)\n"; }
  S(S&&) { std::cout << "S(S &&)\n"; }
};

auto do_something(S const&) -> void {
  std::cout << "do_something(S const &)\n";
}
auto do_something(S&&) -> void {
  std::cout << "do_something(S &&)\n";
}

template <typename T>
auto log_and_do(T&& t) -> void {
  std::cout << "logging!\n";
  do_something(std::forward<T>(t));
}

auto main(int argc, char** argv) -> int {
  S s{};

  std::cout << "--- calling log_and_do(s)\n";
  log_and_do(s);  // lvalue

  S const sc{};
  std::cout << "--- calling log_and_do(sc)\n";
  log_and_do(sc);  // lvalue

  std::cout << "--- calling log_and_do(S{})\n";
  log_and_do(S{});  // rvalue

  std::cout << "--- end\n";
}
