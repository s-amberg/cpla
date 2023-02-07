#include <cstddef>
#include <iostream>
#include <string>


namespace mystring {

inline auto operator"" _s(char const* s, std::size_t len) -> std::string {
  return std::string{s, len};
}

inline auto operator"" _s(char const* s) -> std::string {
  return std::string{s};
}

}  // namespace mystring

auto main(int argc, char** argv) -> int {
  using namespace mystring;
  auto s = "hello"_s;
  s += " world\n";
  std::cout << s;

  auto rs = 42_s;
  rs += " raw\n";
  std::cout << rs;
}
