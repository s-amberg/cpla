#ifndef PEER_NULLPEER_H_
#define PEER_NULLPEER_H_

#include "Peer.h"

#include "../game/Board.h"
#include "../state/PeerState.hpp"

struct NullPeer : Peer {
	virtual void send(Column column) override {
	}
	virtual void connect() override {
	}
	virtual void disconnect() override {
	}
	virtual PeerState const & peerState() override {
		return state;
	}

private:
	PeerState state { //
		"Local Game", //
		[] { return true; }, //
		[] { return false; } //
	};
};


#endif /* PEER_NULLPEER_H_ */
