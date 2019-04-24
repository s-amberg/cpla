#ifndef CONNECTFOURCONTROLLER_H_
#define CONNECTFOURCONTROLLER_H_

#include "ConnectFour.h"
#include "peer/Peer.h"

#include <memory>
#include <optional>
#include <utility>
#include <mutex>
#include <string>

struct ConnectFourController {

	explicit ConnectFourController(std::unique_ptr<Peer> peer) :
			peer { std::move(peer) } {
		this->peer->connect();
	}

	void disconnect() {
		this->peer->disconnect();
	}

	void drop(Column column) {
		try {
			if (peer->canSend()) {
				dropLocal(column);
				peer->send(column);
			}
		} catch (ColumnFullException const &) {
			//ignore
		}
	}

	void dropLocal(Column column) {
		std::lock_guard guard { m };
		game.drop(column);
	}

	std::optional<Index> latest() const {
		std::lock_guard guard { m };
		return game.latest();
	}

	Row rows() const {
		return game.rows();
	}

	Column columns() const {
		return game.columns();
	}

	ConnectFour::BoardType::State at(Row row, Column column) const {
		return game.getBoard().at(row, column);
	}

	ConnectFour::BoardType board() const {
		std::lock_guard guard { m };
		return game.getBoard();
	}

	std::string peerName() const {
		return peer->name();
	}
private:
	mutable std::mutex m { };
	ConnectFour game { };
	std::unique_ptr<Peer> peer;
};

#endif /* CONNECTFOURCONTROLLER_H_ */
