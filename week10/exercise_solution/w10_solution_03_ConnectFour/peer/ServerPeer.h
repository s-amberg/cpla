#ifndef PEER_SERVERPEER_H_
#define PEER_SERVERPEER_H_


#include "Peer.h"

#include "../game/Board.h"
#include "../game/ConnectFour.h"
#include "../game/GameCommand.hpp"

#include "../state/PeerState.hpp"

#include "asio/error.hpp"
#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/read.hpp"
#include "asio/write.hpp"

#include <functional>
#include <memory>
#include <system_error>
#include <string>
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

struct ServerPeer: Peer {
	ServerPeer(asio::io_context & context, unsigned short port, std::function<void(Column)> callback) :
			acceptor { context, asio::ip::tcp::endpoint { asio::ip::tcp::v4(), port } }, callback { callback } {
	}

	virtual void send(Column column) override {
		if (state.canSend()) {
			session->send(std::make_shared<GameCommand>(column));
		}
	}

	virtual void connect() override {
		if (!acceptor.is_open()) {
			acceptor.open(asio::ip::tcp::v4());
		}
		doAccept();
	}

	virtual void disconnect() override {
		closeSession();
		std::error_code ignored { };
		acceptor.cancel(ignored);
		acceptor.close(ignored);
	}

	virtual PeerState const & peerState() override {
		return state;
	}

private:
	asio::ip::tcp::acceptor acceptor;
	std::function<void(Column)> callback;
	std::shared_ptr<GameSession> session { nullptr };
	PeerState state { //
		"Server", //
		[this]() -> bool { return session && session->sessionState().canSend; }, //
		[this]() -> bool { return session && session->sessionState().connected; }, //
		ConnectFour::Player::Yellow
	};

	void closeSession() {
		session = nullptr;
	}

	void doAccept() {
		acceptor.async_accept([this](std::error_code const error, asio::ip::tcp::socket && socket) {
			if (!error && !session) {
				session = std::make_shared<GameSession>(std::move(socket), callback);
			}
			if (!state.connected()) {
				closeSession();
			}
			if (error != asio::error::basic_errors::operation_aborted) {
				doAccept();
			}
		});
	}

};

#endif /* PEER_SERVERPEER_H_ */
