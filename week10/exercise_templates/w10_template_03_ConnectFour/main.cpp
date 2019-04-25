#include "ConnectFourWindow.h"

#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"

#include <charconv>
#include <iostream>
#include <string_view>
#include <thread>

static auto parsePort(std::string_view port) -> unsigned short {
	unsigned short result { };
	std::from_chars(port.cbegin(), port.cend(), result);
	return result;
}

static auto endpoints(asio::io_context & context, std::string_view host, std::string_view port) -> asio::ip::tcp::resolver::results_type {
	asio::ip::tcp::resolver resolver { context };
	return resolver.resolve(host, port);
}

static void runGame(asio::io_context & context, ConnectFourWindow & gui) {
	std::thread network { [&context]() {context.run();} };
	gui.run();
	network.join();
}

static void singlePlayerGame() {
	ConnectFourWindow gui { };
	gui.run();
}

static void serverGame(std::string_view port) {
	asio::io_context context { };
	ConnectFourWindow gui { context, parsePort(port) };
	runGame(context, gui);
}

static void clientGame(std::string_view host, std::string_view port) {
	asio::io_context context { };
	ConnectFourWindow gui { context, endpoints(context, host, port) };
	runGame(context, gui);
}

int main(int argc, char const * argv[]) {
	if (argc == 1) {
		std::cout << "Starting single-player.\n";
		singlePlayerGame();
		return EXIT_SUCCESS;
	}

	switch (argc) {
	case 2:
		std::cout << "Starting server.\n";
		serverGame(argv[1]);
		break;
	case 3:
		std::cout << "Starting client.\n";
		clientGame(argv[1], argv[2]);
		break;
	default:
		std::cout << "Too many arguments.\n" //
				<< "Usage:\n" //
				<< "Single-player: ConnectFourGui\n" //
				<< "Server: ConnectFourGui <port>\n" //
				<< "Client: ConnectFourGui <server-ip> <port>\n";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
