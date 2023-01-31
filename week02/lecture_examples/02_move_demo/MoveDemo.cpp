#include <iostream>

struct MoveableThing {
  MoveableThing() { std::cout << "Create Thing\n"; }
  MoveableThing(MoveableThing&&) { std::cout << "Move Thing\n"; }
};

auto create() -> MoveableThing {
  MoveableThing t{};
  return t;
}

auto main() -> int {
  MoveableThing created = create();
}
