#ifndef CONNECTFOURCONTROLLER_H_
#define CONNECTFOURCONTROLLER_H_

#include "ConnectFour.h"
#include "peer/Peer.h"

#include <memory>
#include <optional>
#include <utility>

struct ConnectFourController {

	explicit ConnectFourController(std::unique_ptr<Peer> peer) : peer{std::move(peer)} {

	}

	void drop(Column column) {
		try {
			game.drop(column);
			peer->send(column);
		} catch (ColumnFullException const &) {
			//ignore
		}
	}
	std::optional<Index> latest() const {
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
private:
	ConnectFour game{};
	std::unique_ptr<Peer> peer;
};


#endif /* CONNECTFOURCONTROLLER_H_ */
