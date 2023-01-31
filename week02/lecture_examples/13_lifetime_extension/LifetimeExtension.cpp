#include <iostream>

struct Demon {
  //...
};

auto summon() -> Demon {
  return Demon{};
}

auto count_eyes(Demon const&) -> void {
  //...
}

auto blood_magic() -> Demon const& {
  Demon breknok{};
  return breknok;
}  // When blood_magic ends, breknok dies and will stay dead. All access will be
   // Undefined Behavior!

auto animate(Demon const& demon) -> Demon const& {
  //...
  return demon;
}

auto main() -> int {
  summon();  // Demon dies at the end of the statement

  count_eyes(Demon{});  // Demon lives long enough for count_eyes to finish

  Demon const& flaaghun = summon();  // Life-time can be extended by const &,
                                     // flaaghun lives until end of block

  Demon&& laznik = summon();  // Life-time can also be extended by &&, laznik
                              // lives until end of block

  Demon const& breknok =
      blood_magic();  // You cannot keep demon from blood_magic alive! Access to
                      // breknok is Undefined Behavior

  std::cout << "---\n";
  Demon const& knoorus =
      animate(Demon{});  // You cannot keep demon passed through animate alive!
                         // Access to knoorus is Undefined Behavior
  std::cout << "---\n";

}  // flaaghun and laznik die
