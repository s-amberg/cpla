#ifndef PEER_SERVERPEER_H_
#define PEER_SERVERPEER_H_

#include "Peer.h"

struct ServerPeer : Peer {
	explicit ServerPeer(unsigned short port) : port{port} {
	}
	virtual void send(Column column) override {
	}
	virtual void connect() override {
	}
	virtual void disconnect() override {
	}
	virtual void restart() override {
	}
private:
	unsigned short port;
};


#endif /* PEER_SERVERPEER_H_ */
