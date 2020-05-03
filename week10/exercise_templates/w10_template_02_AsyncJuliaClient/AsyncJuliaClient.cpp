#include "JuliaClient.h"

#include "asio.hpp"

int main() {
	auto context = asio::io_context { };
	auto client = JuliaClient { context, "127.0.0.1", 8080 };
	client.download_image();
	context.run();
}
