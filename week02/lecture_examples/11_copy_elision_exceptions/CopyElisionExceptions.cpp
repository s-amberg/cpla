#include <iostream>
#include <utility>


struct S {
  S() { std::cout << "creating S\n"; }

  //	S(S const &) = delete;

  S(S const&) { std::cout << "copying S\n"; }
};

auto main() -> int {
  try {
    S s{};
    throw s;
  } catch (S s) {
  }
}
