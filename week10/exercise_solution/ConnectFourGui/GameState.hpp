#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include "ConnectFour.h"

#include "peer/PeerState.hpp"

#include <string>
#include <optional>

struct GameState {
	PeerState const & peerState;
	std::optional<ConnectFour::Player> winner { std::nullopt };

	std::string toString() const {
		return peerState.toString();
	}
};


#endif /* GAMESTATE_HPP_ */
