#include "simple_http.h"
#include "asio.hpp"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <sstream>

int main()
try {
	auto context = asio::io_context { };

	auto server_address = asio::ip::make_address("127.0.0.1");
	auto server_endpoint = asio::ip::tcp::endpoint { server_address, 8080 };
	auto socket = asio::ip::tcp::socket { context };
	socket.connect(server_endpoint);

	auto request = std::ostringstream { };
	request << http::request { http::method::get };
	auto request_data = request.str();

	asio::write(socket, asio::buffer(request_data));

	auto response_buffer = asio::streambuf { };
	auto response_stream = std::istream { &response_buffer };
	asio::read_until(socket, response_buffer, "\r\n\r\n");

	auto response = http::response { response_stream };

	if (!response.complete()) {
		auto content_length = response.get<http::header::content_length>();
		auto buffered = response_buffer.size();
		asio::read(socket, response_buffer, asio::transfer_exactly(content_length - buffered));
		response.body(response_stream);
	}

	if (response.status() != http::status_code::ok) {
		std::cerr << "Server did not accept the request: " << to_string(response.status()) << '\n';
		return EXIT_FAILURE;
	}

	auto file = std::ofstream { "julia.bmp", std::ios::trunc | std::ios::binary };
	auto image_data = response.body();
	copy(cbegin(image_data), cend(image_data), std::ostream_iterator<char> { file });
	file.close();

	std::cout << "Successfully received Julia fractal from the server. Result is in julia.bmp\n";
}
catch (asio::error_code const &error) {
	std::cerr << "Failed to download the Julia fractal: " << error.message() << '\n';
}
