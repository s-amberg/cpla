#ifndef PEER_NULLPEER_H_
#define PEER_NULLPEER_H_

#include "Peer.h"


struct NullPeer : Peer {
	virtual void send(Column column) override {
	}
	virtual void connect() override {
	}
	virtual void disconnect() override {
	}
	virtual void restart() override {
	}
};


#endif /* PEER_NULLPEER_H_ */
