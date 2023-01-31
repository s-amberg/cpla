#include <iostream>

struct Ghost {
  auto haunt() const -> void { std::cout << "booooo!\n"; }
  //~Ghost() = delete;
};

auto evoke() -> Ghost {
  return Ghost{};
}

auto main() -> int {
  Ghost&& sam = evoke();

  Ghost{}.haunt();
}
