#include "simple_http.h"
#include "asio.hpp"

#include <algorithm>
#include <fstream>
#include <istream>
#include <iterator>
#include <sstream>

int main()
{
	auto context = asio::io_context{};

	auto resolver = asio::ip::tcp::resolver{context};
	auto resolved = resolver.resolve("127.0.0.1", "8080");

	auto socket = asio::ip::tcp::socket{context};
	asio::connect(socket, resolved);

	auto request = std::ostringstream{};
	request << http::request{http::method::get};
	auto request_data = request.str();

	asio::write(socket, asio::buffer(request_data));

	auto response_buffer = asio::streambuf{};
	auto response_stream = std::istream{&response_buffer};
	asio::read_until(socket, response_buffer, "\r\n\r\n");

	auto response = http::response{response_stream};

	if(!response.complete()) {
		auto content_length = response.get<http::header::content_length>();
		auto buffered = response_buffer.size();
		asio::read(socket, response_buffer, asio::transfer_exactly(content_length - buffered));
		response.body(response_stream);
	}

	auto file = std::ofstream{"julia.bmp", std::ios::trunc | std::ios::binary};
	auto image_data = response.body();
	copy(cbegin(image_data), cend(image_data), std::ostream_iterator<char>{file, ""});
}
