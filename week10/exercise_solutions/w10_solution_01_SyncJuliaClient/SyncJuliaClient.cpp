#include "simple_http.h"
#include "asio.hpp"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <sstream>

int main() {
	auto context = asio::io_context { };

	auto error = asio::error_code { };

	auto resolver = asio::ip::tcp::resolver { context };
	auto resolved = resolver.resolve("127.0.0.1", "8080", error);

	if (error) {
		std::cerr << "Failed to resolve server address: " << error.message() << '\n';
		return EXIT_FAILURE;
	}

	auto socket = asio::ip::tcp::socket { context };
	asio::connect(socket, resolved, error);

	if (error) {
		std::cerr << "Failed to connect to server: " << error.message() << '\n';
		return EXIT_FAILURE;
	}

	auto request = std::ostringstream { };
	request << http::request { http::method::get };
	auto request_data = request.str();

	asio::write(socket, asio::buffer(request_data), error);

	if (error) {
		std::cerr << "Failed to send request: " << error.message() << '\n';
		return EXIT_FAILURE;
	}

	auto response_buffer = asio::streambuf { };
	auto response_stream = std::istream { &response_buffer };
	asio::read_until(socket, response_buffer, "\r\n\r\n", error);

	if (error) {
		std::cerr << "Failed to read response headers: " << error.message() << '\n';
		return EXIT_FAILURE;
	}

	auto response = http::response { response_stream };

	if (!response.complete()) {
		auto content_length = response.get<http::header::content_length>();
		auto buffered = response_buffer.size();
		asio::read(socket, response_buffer, asio::transfer_exactly(content_length - buffered), error);

		if (error) {
			std::cerr << "Failed to read response body: " << error.message() << '\n';
			return EXIT_FAILURE;
		}

		response.body(response_stream);
	}

	if(response.status() != http::status_code::ok) {
		std::cerr << "Server did not accept the request: " << to_string(response.status()) << '\n';
		return EXIT_FAILURE;
	}

	auto file = std::ofstream { "julia.bmp", std::ios::trunc | std::ios::binary };
	auto image_data = response.body();
	copy(cbegin(image_data), cend(image_data), std::ostream_iterator<char> { file, "" });
	file.close();

	std::cout << "Successfully received Julia fractal from the server. Result is in julia.bmp\n";
}
