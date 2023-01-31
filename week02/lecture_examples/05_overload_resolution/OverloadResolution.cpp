#include <iostream>
#include <utility>

struct S {
  S() = default;
  S(S const&) { std::cout << "S(S const&)\n"; }
  S(S&&) { std::cout << "S(S&&)\n"; }
  auto operator=(S&&) -> S& {
    std::cout << "operator=(S&&)\n";
    return *this;
  }
};

auto createS(S& s) -> S {
  return s;
}

// auto f(S param) -> void {
//	std::cout << "f(S)\n";
// }

auto f(S& param) -> void {
  std::cout << "f(S &)\n";
}

auto f(S const& param) -> void {
  std::cout << "f(S const &)\n";
}

auto f(S&& param) -> void {
  std::cout << "f(S &&)\n";
}

auto main(int argc, char** argv) -> int {
  S s{};
  f(s);

  S const cs{};
  f(cs);

  f(S{});

  f(std::move(s));

  f(createS(s));
}
