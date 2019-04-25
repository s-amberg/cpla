#ifndef PEER_PEERSTATE_HPP_
#define PEER_PEERSTATE_HPP_

#include "../game/ConnectFour.h"

#include "asio/ip/tcp.hpp"

#include <atomic>
#include <string>

struct PeerState {
	std::string name { "Unknown" };
	ConnectFour::Player player { ConnectFour::Player::Red };
	std::atomic_bool canSend { false };
	std::atomic_bool connected { false };

	std::string toString() const {
		std::string connectedString { connected ? "Connected" : "No Connection" };
		std::string turnString { canSend ? "Your Turn!" : "Opponents Turn!" };
		std::string colorString { player == ConnectFour::Player::Red ? "Red" : "Yellow" };
		return connectedString + " | You play as " + colorString + "  |  " + turnString;
	}
};

#endif /* PEER_PEERSTATE_HPP_ */
