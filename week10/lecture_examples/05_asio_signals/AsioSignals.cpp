#include <asio.hpp>

#include <csignal>
#include <iostream>

int main() {
	auto context = asio::io_context { };

	auto signals = asio::signal_set { context, SIGINT, SIGTERM };
	signals.async_wait([&](auto error, auto sig) {
		if (!error) {
			std::cout << "received signal: " << sig << '\n';
		} else {
			std::cout << "signal handling aborted\n";
		}
	});

	context.run();
}
