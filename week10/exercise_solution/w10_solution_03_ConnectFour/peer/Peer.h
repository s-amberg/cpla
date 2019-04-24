#ifndef PEER_PEER_H_
#define PEER_PEER_H_

#include <string>

struct Peer {
	virtual ~Peer() = default;
	virtual void send(Column column) = 0;
	virtual void connect() = 0;
	virtual void disconnect() = 0;
	virtual bool canSend() const = 0;
	virtual std::string name() const = 0;
};



#endif /* PEER_PEER_H_ */
