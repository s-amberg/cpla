#include <iostream>

struct CopyableThing {
  CopyableThing() { std::cout << "Create Thing\n"; }
  CopyableThing(CopyableThing const&) { std::cout << "Copy Thing\n"; }
};

auto create() -> CopyableThing {
  CopyableThing t{};
  return t;
}

auto main() -> int {
  CopyableThing created = create();
}
