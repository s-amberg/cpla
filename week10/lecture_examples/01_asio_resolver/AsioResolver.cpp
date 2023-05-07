#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <asio.hpp>

auto resolve(std::string_view host) -> std::vector<std::string> {
  std::vector<std::string> addresses{};
  auto context = asio::io_context{};
  auto resolver = asio::ip::tcp::resolver{context};
  auto endpoints = resolver.resolve(asio::ip::tcp::v4(), host.data(), "");
  transform(std::cbegin(endpoints), std::cend(endpoints), std::back_inserter(addresses), [](asio::ip::tcp::endpoint endpoint) { return endpoint.address().to_string(); });
  return addresses;
}

auto main(int argc, char const *argv[]) -> int {
  auto host = std::string{};
  if (argc == 1) {
    host = "www.ost.ch";
  } else {
    host = argv[1];
  }
  auto addresses = resolve(host);
  std::cout << "Addresses for: " << host << '\n';
  copy(cbegin(addresses), cend(addresses), std::ostream_iterator<std::string>{std::cout, "\n"});
}
