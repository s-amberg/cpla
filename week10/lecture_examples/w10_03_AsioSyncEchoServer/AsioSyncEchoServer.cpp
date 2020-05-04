

#include <array>
#include <iostream>
#include <string>
#include <cstdlib>

#include <asio.hpp>
#include <sstream>


//
//void getUrl(std::string_view domain) {
//	asio::io_context context{};
//	asio::ip::tcp::socket socket{context};
//	asio::ip::tcp::resolver resolver{context};
//	auto endpoints = resolver.resolve(domain, "80");
//	asio::connect(socket, endpoints);
//
//	std::ostringstream request{};
//	request << "GET / HTTP/1.1\r\n";
//	request << "Host: " << domain << "\r\n";
//	request << "\r\n";
//	asio::write(socket, asio::buffer(request.str()));
//	socket.shutdown(asio::ip::tcp::socket::shutdown_send);
//
//	constexpr size_t bufferSize = 1024;
//    std::array<char, bufferSize> reply{};
//    asio::error_code errorCode{};
//	  do {
//		auto readLength = asio::read(socket, asio::buffer(reply.data(), bufferSize), errorCode);
//		if (errorCode == asio::error::eof) {
//		  std::cout << "finished" << std::endl;
//		  return;
//		} else if (errorCode) {
//			throw asio::system_error{errorCode};
//		}
//		std::cout << "Data received: ";
//		std::cout.write(reply.data(), readLength);
//		std::cout << std::endl;
//	} while (true);
//}

void runEchoServer(unsigned short port) {
	asio::io_context context{};
	asio::ip::tcp::endpoint localEndpoint{asio::ip::tcp::v4(), port};
	asio::ip::tcp::acceptor acceptor{context, localEndpoint};
	acceptor.set_option(asio::ip::tcp::socket::reuse_address{});

	std::cout << "accepting connections on: " << localEndpoint << std::endl;

	asio::ip::tcp::endpoint peerEndpoint{};
	asio::ip::tcp::socket peerSocket = acceptor.accept(peerEndpoint);

	std::cout << "connection established with: " << peerEndpoint << std::endl;

	  do {
		std::string message{};
	    asio::error_code errorCode{};
		auto readLength = asio::read_until(peerSocket, asio::dynamic_buffer(message), '\n', errorCode);
		if (errorCode == asio::error::eof) {
			peerSocket.shutdown(asio::ip::tcp::socket::shutdown_both);
		  std::cout << "finished" << std::endl;
		  return;
		} else if (errorCode) {
			throw asio::system_error{errorCode};
		}
		std::cout << "Data received " << readLength << " byte: ";
		std::cout << message;
		std::cout << std::endl;
		asio::write(peerSocket, asio::buffer(message.c_str(), readLength));
		std::cout << "Reply sent" << std::endl;
	} while (true);
}

int main(int argc, char const * argv[]) {
	unsigned short port;
	if (argc > 1) {
		port = std::stoul(argv[1], nullptr, 10);
	} else {
		port = 1234;
	}
	try {
		runEchoServer(port);
	} catch (asio::system_error const & e) {
		std::cout << "An error occurred: " << e.what();
	}
}
