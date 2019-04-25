#ifndef PEER_NULLPEER_H_
#define PEER_NULLPEER_H_

#include "Peer.h"

#include "../game/Board.h"
#include "../game/ConnectFour.h"
#include "../state/PeerState.hpp"

struct NullPeer : Peer {
	virtual void send(Column column) override {
	}
	virtual void connect() override {
	}
	virtual void disconnect() override {
	}
	virtual PeerState const & peerState() const override {
		return state;
	}

private:
	PeerState const state { //
		"Local Game", //
		ConnectFour::Player::Red, //
		true, //
		true //
	};
};


#endif /* PEER_NULLPEER_H_ */
