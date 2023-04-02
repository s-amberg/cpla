
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

// auto operator<<(std::ostream& os, Date const& date) -> std::ostream& {
//   date.print(os);
//   return os;
// }


template <typename T>
concept LeftshiftOutputtable = requires (T const v, std::ostream& os) { {os << v} -> std::same_as<std::ostream&>; };

template <typename T>
concept Printable = requires (T const v, std::ostream& os) { 
  v.print(os);
};

auto print(Printable auto const& printable) {
  printable.print(std::cout);
}

auto print(LeftshiftOutputtable auto const& outputtable) {
  std::cout << outputtable;
}

auto printAll(auto const& first, auto const&... rest) -> void {
  print(first);
  if constexpr (sizeof...(rest)) {
    std::cout << ", ";
    printAll(rest...);
  }
}


auto main() -> int {
  using namespace std::string_literals;
  Date d{4, 4, 2023};
  printAll(1, 2.0, 3, "four", "five"s, d);
}