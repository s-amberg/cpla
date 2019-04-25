#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include "PeerState.hpp"

#include "../game/ConnectFour.h"

#include <optional>

struct GameState {
	PeerState const & peerState;
	std::optional<ConnectFour::Player> winner { std::nullopt };
};


#endif /* GAMESTATE_HPP_ */
