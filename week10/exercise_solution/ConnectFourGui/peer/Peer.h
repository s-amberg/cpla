#ifndef PEER_PEER_H_
#define PEER_PEER_H_

#include "Board.h"

struct Peer {
	virtual ~Peer() = default;
	virtual void send(Column column) = 0;
	virtual void connect() = 0;
	virtual void disconnect() = 0;
	virtual void restart() = 0;
};



#endif /* PEER_PEER_H_ */
