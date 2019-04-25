#ifndef PEER_PEER_H_
#define PEER_PEER_H_

#include "../game/Board.h"
#include "../state/PeerState.hpp"

struct Peer {
	virtual ~Peer() = default;
	virtual void send(Column column) = 0;
	virtual void connect() = 0;
	virtual void disconnect() = 0;
	virtual PeerState const & peerState() = 0;
};



#endif /* PEER_PEER_H_ */
