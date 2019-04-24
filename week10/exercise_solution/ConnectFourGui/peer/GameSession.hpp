#ifndef PEER_GAMESESSION_HPP_
#define PEER_GAMESESSION_HPP_

#include "Board.h"
#include "GameCommand.hpp"

#include "asio/ip/tcp.hpp"
#include "asio/read.hpp"
#include "asio/write.hpp"

#include <functional>
#include <system_error>
#include <memory>
#include <utility>

struct GameSesssionState {
	bool canSend { false };
	bool connected { false };
};

struct GameSession: std::enable_shared_from_this<GameSession> {
	GameSession(asio::ip::tcp::socket socket, std::function<void(Column)> callback) :
			socket { std::move(socket) }, callback { callback } {
		state.connected = true;
		doRead();
	}

	~GameSession() {
		if (socket.is_open()) {
			std::error_code ignored { };
			socket.shutdown(asio::ip::tcp::socket::shutdown_both, ignored);
			socket.close(ignored);
		}
	}

	void send(std::shared_ptr<GameCommand> gc) {
		if (state.canSend) {
			doSend(gc);
		}
	}

	GameSesssionState const & sessionState() const {
		return state;
	}

private:
	asio::ip::tcp::socket socket;
	std::function<void(Column)> callback;
	GameCommand receivedCommand { };
	GameSesssionState state { };

	void doRead() {
		asio::async_read(socket, receivedCommand.asBuffer(), [this](std::error_code ec, auto) {
			if (!ec) {
				callback(receivedCommand.decode());
				state.canSend = true;
				doRead();
			} else if (ec == asio::error::eof) {
				state.connected = false;
				state.canSend = false;
			}
		});
	}

	void doSend(std::shared_ptr<GameCommand> gc) {
		asio::async_write(socket, gc->asBuffer(), [this, gc](std::error_code ec, auto) {
			state.canSend = false;
		});
	}
};



#endif /* PEER_GAMESESSION_HPP_ */
