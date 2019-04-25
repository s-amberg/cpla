#ifndef CONNECTFOURCONTROLLER_H_
#define CONNECTFOURCONTROLLER_H_

#include "game/Board.h"
#include "game/ConnectFour.h"

#include "state/GameState.hpp"

#include "peer/Peer.h"

#include <memory>
#include <optional>
#include <utility>
#include <mutex>

struct ConnectFourController {

	explicit ConnectFourController(std::unique_ptr<Peer> peer) :
			peer { std::move(peer) } {
		this->peer->start();
	}

	void disconnect() {
		this->peer->stop();
	}

	void drop(Column column) {
		try {
			if (peer->peerState().canSend && !state.winner) {
				dropLocal(column);
				peer->send(column);
			}
		} catch (ColumnFullException const &) {
			//ignore
		}
	}

	void resetGame() {
		if (game.hasStarted()) {
			game = ConnectFour { };
			state.winner = std::nullopt;
		}
	}

	void dropLocal(Column column) {
		state.winner = game.drop(column);
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

	ConnectFour::BoardType board() const {
		return game.getBoard();
	}

	GameState const & gameState() const {
		return state;
	}

private:
	std::unique_ptr<Peer> peer;
	ConnectFour game { };
	GameState state { peer->peerState() };
};

#endif /* CONNECTFOURCONTROLLER_H_ */
