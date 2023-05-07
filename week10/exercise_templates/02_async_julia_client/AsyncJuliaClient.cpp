#include "JuliaClient.hpp"

#include "asio.hpp"

auto main() -> int {
	auto context = asio::io_context { };
	auto client = JuliaClient { context, "127.0.0.1", 8080 };
	client.download_image();
	context.run();
}
