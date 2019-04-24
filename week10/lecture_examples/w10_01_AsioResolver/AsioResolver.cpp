#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <asio.hpp>

std::vector<std::string> resolve(std::string_view host) {
	std::vector<std::string> addresses{};
	asio::io_context context{};
	asio::ip::tcp::resolver resolver{context};
	auto endpoints = resolver.resolve(asio::ip::tcp::v4(), host.data(), "");
	std::transform(std::begin(endpoints), std::end(endpoints), std::back_inserter(addresses), [](asio::ip::tcp::endpoint endpoint) {
		return endpoint.address().to_string();
	});
	return addresses;
}

int main(int argc, char const * argv[]) {
	std::string host{};
	if (argc == 1) {
		host = "www.hsr.ch";
	} else {
		host = argv[1];
	}
	auto addresses = resolve(host);
	std::cout << "Addresses for: " << host << '\n';
	std::copy(std::begin(addresses), std::end(addresses), std::ostream_iterator<std::string>{std::cout, "\n"});
}
