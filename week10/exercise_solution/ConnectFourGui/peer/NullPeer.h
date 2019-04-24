#ifndef PEER_NULLPEER_H_
#define PEER_NULLPEER_H_

#include "Peer.h"

#include <string>

struct NullPeer : Peer {
	virtual void send(Column column) override {
	}
	virtual void connect() override {
	}
	virtual void disconnect() override {
	}
	virtual bool canSend() const override {
		return true;
	}
	virtual std::string name() const override {
		return "Null";
	}
};


#endif /* PEER_NULLPEER_H_ */
