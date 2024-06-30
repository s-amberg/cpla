#include <iomanip>
#include <ios>
#include <iostream>
#include <thread>

//will likely only "work" on 32-bit systems
//-m32 Needs 32-Bit Compiler!

struct Flipper {
  auto flip() -> void {
    while (true) {
      value = ~value;
    }
  }
  auto get() const -> long long {
    return value;
  }

private:
  long long value{0};
};

auto main(int argc, char **argv) -> int {
  // Flipper flipper{};
  // std::jthread flipperThread{[&] { flipper.flip(); }};
  // std::cout << std::hex;
  // while (true) {
  //   auto tmp = flipper.get();
  //   if (tmp != 0ll && tmp != ~0ll) {
  //     std::cout << "Surprise! Value is 0x" << std::setw(sizeof(tmp) * 2) << std::setfill('0') << tmp << std::endl;
  //   }
  // }
}
