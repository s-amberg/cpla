
#include "ConnectFourWindow.h"
#include "SFML/Network/IpAddress.hpp"

#include <cstdlib>

static unsigned short parsePort(char const * port) {
	return std::strtoul(port, nullptr, 10);
}

static sf::IpAddress parseAddress(char const * host) {
	return sf::IpAddress{host};
}

static void singlePlayerGame() {
	ConnectFourWindow gui{};
	gui.run();
}

static void serverGame(char const * port) {
	auto serverPort = parsePort(port);
	ConnectFourWindow gui{serverPort};
	gui.run();
}

static void clientGame(char const * host, char const * port) {
	auto serverAddress = parseAddress(host);
	auto serverPort = parsePort(port);
	ConnectFourWindow gui{serverAddress, serverPort};
	gui.run();
}

int main(int argc, char const * argv[]) {
	switch (argc) {
	case 1:
		singlePlayerGame();
		break;
	case 2:
		serverGame(argv[1]);
		break;
	case 3:
		clientGame(argv[1], argv[2]);
		break;
	}

}
