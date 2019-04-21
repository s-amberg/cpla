#ifndef PEER_CLIENTPEER_H_
#define PEER_CLIENTPEER_H_

#include "Peer.h"

#include <SFML/Network/IpAddress.hpp>

struct ClientPeer : Peer {
	ClientPeer(sf::IpAddress address, unsigned short port) : address{address}, port{port}{}
	virtual void send(Column column) override {
	}
	virtual void connect() override {
	}
	virtual void disconnect() override {
	}
	virtual void restart() override {
	}
private:
	sf::IpAddress address;
	unsigned short port;
};



#endif /* PEER_CLIENTPEER_H_ */
