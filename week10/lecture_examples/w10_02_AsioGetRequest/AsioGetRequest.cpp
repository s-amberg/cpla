

#include <array>
#include <iostream>
#include <string>

#include <asio.hpp>
#include <sstream>


void getUrl(std::string_view domain) {
	asio::io_context context{};
	asio::ip::tcp::socket socket{context};
	asio::ip::tcp::resolver resolver{context};
	auto endpoints = resolver.resolve(domain, "80");
	asio::connect(socket, endpoints);

	std::ostringstream request{};
	request << "GET / HTTP/1.1\r\n";
	request << "Host: " << domain << "\r\n";
	request << "\r\n";
	asio::write(socket, asio::buffer(request.str()));
	socket.shutdown(asio::ip::tcp::socket::shutdown_send);
	 do {
		constexpr size_t bufferSize = 1024;
		std::array<char, bufferSize> reply{};
		asio::error_code errorCode{};
		auto readLength = asio::read(socket, asio::buffer(reply.data(), bufferSize), errorCode);
		if (errorCode == asio::error::eof) {
		  std::cout << "finished" << std::endl;
		  return;
		} else if (errorCode) {
			throw asio::system_error{errorCode};
		}
		std::cout << "Data received: ";
		std::cout.write(reply.data(), readLength);
		std::cout << std::endl;
	} while (true);
	 socket.close();
}


int main(int argc, char const * argv[]) {
	std::string host{};
	if (argc == 1) {
		host = "www.w3.org";
	} else {
		host = argv[1];
	}
	try {
		getUrl(host);
	} catch (asio::system_error const & e) {
		std::cout << "An error occurred: " << e.what();
	}
}
