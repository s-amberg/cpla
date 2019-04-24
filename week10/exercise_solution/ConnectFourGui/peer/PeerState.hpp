#ifndef PEER_PEERSTATE_HPP_
#define PEER_PEERSTATE_HPP_

#include "ConnectFour.h"

#include "asio/ip/tcp.hpp"

#include <functional>
#include <string>

struct PeerState {
	std::string name { "Unknown" };
	std::function<bool()> canSend { [] { return false; } };
	std::function<bool()> connected { [] { return false; } };
	ConnectFour::Player player { ConnectFour::Player::Red };

	std::string toString() const {
		std::string connectedString { connected() ? "Connected" : "No Connection" };
		std::string turnString { canSend() ? "Your Turn!" : "Opponents Turn!" };
		std::string colorString { player == ConnectFour::Player::Red ? "Red" : "Yellow" };
		return connectedString + " | You play as " + colorString + "  |  " + turnString;
	}
};

#endif /* PEER_PEERSTATE_HPP_ */
