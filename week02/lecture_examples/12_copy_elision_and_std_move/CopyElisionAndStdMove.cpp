#include <iostream>
#include <utility>


struct S {
  S() { std::cout << "Constructor S()\n"; }

  //	S(S const &) = delete;

  //	S(S const &) = delete;
  //	S(S &&) = delete;
  S(S const&) { std::cout << "Constructor S(S const &)\n"; }

  S(S&&) { std::cout << "Constructor S(S &&)\n"; }

  auto operator=(S const&) -> S& {
    std::cout << "operator =(S const &)\n";
    return *this;
  }

  auto operator=(S&&) -> S& {
    std::cout << "operator =(S &&)\n";
    return *this;
  }
};

auto create() -> S {
  S s{};
  std::cout << "\t --- create() ---\n";
  return std::move(s);
}

auto main() -> int {
  std::cout << "\t --- S s{create()} ---\n";
  S s{create()};
}
