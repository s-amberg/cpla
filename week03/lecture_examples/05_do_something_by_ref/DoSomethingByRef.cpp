#include <boost/type_index.hpp>
#include <iostream>


struct S {
  S() = default;
  S(S const&) { std::cout << "S(S const &) -> copy\n"; }
  S(S&&) { std::cout << "S(S &&) -> move\n"; }
};

auto do_something(S const&) -> void {
  std::cout << "do_something(S const &)\n";
}
auto do_something(S&&) -> void {
  std::cout << "do_something(S &&)\n";
}

template <typename T>
auto log_and_do(T& t) -> void {
  std::cout << "logging!\n";
  do_something(t);
}

auto main(int argc, char** argv) -> int {
  S s{};

  std::cout << "--- calling log_and_do(s)\n";
  log_and_do(s);  // lvalue

  std::cout << "--- calling log_and_do(S{})\n";
  //	log_and_do(S{}); //rvalue - does not compile

  std::cout << "--- end\n";
}
