#include <cstring>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>


namespace ternary {
inline auto operator"" _3(char const* s) -> unsigned long long {
  size_t convertedupto{};
  auto res = std::stoull(s, &convertedupto, 3u);
  if (convertedupto != strlen(s))
    throw std::logic_error{"invalid ternary"};
  return res;
}

}  // namespace ternary

auto main(int argc, char** argv) -> int {
  using namespace ternary;
  int four = 11_3;
  std::cout << "four is " << four << '\n';
  try {
    four = 14_3;  // throws
  } catch (std::exception const& e) {
    std::cout << e.what() << '\n';
  }
}
