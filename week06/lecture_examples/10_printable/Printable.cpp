
#include <iostream>
#include <string>

struct Date {

  Date(unsigned day, unsigned month, unsigned year) : day{day}, month{month}, year{year}{}

  auto print(std::ostream& os) const -> void {
    os << day << "/" << month << "/" << year;
  }

private:
   unsigned day;
   unsigned month;
   unsigned year;
};


template <typename T>
concept Printable = requires (T const v, std::ostream& os) { v.print(os); };

template <typename T>
concept LeftshiftOutputtable = requires (T const v, std::ostream& os) { {os << v} -> std::same_as<std::ostream&>; };


auto operator<<(std::ostream& os, Printable auto const & value) -> std::ostream& {
  value.print(os);
  return os;
}

template <typename First, typename... Types>
auto printAll(First const& first, Types const&... rest) -> void {
  std::cout << first;
  if constexpr (sizeof...(Types)) {
    std::cout << ", ";
    printAll(rest...);
  }
}

// template <LeftshiftOutputtable First, LeftshiftOutputtable... Types>
// auto printAll(First const& first, Types const&... rest) -> void {
//   std::cout << first;
//   if constexpr (sizeof...(Types)) {
//     std::cout << ", ";
//     printAll(rest...);
//   }
// }


auto main() -> int {
  using namespace std::string_literals;
  Date d{4, 4, 2023};
  // printAll(1, 2.0, 3, "four", "five"s, d);
}