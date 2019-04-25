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
#include <optional>
#include <system_error>
#include <utility>


struct ServerPeer: Peer {
	ServerPeer(asio::io_context & context, unsigned short port, std::function<void(Column)> callback) :
			acceptor { context, asio::ip::tcp::endpoint { asio::ip::tcp::v4(), port } }, callback { callback } {
	}

	virtual void send(Column column) override {
		if (state.canSend) {
			doSend(std::make_shared<GameCommand>(column));
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

	virtual PeerState const & peerState() const override {
		return state;
	}

private:
	asio::ip::tcp::acceptor acceptor;
	std::function<void(Column)> callback;
	std::optional<asio::ip::tcp::socket> socket { std::nullopt };
	GameCommand receivedCommand { };
	PeerState state { //
		"Server", //
		ConnectFour::Player::Yellow
	};

	void closeSession() {
		socket = std::nullopt;
	}

	void doAccept() {
		acceptor.async_accept([this](std::error_code const error, asio::ip::tcp::socket && socket) {
			if (!error && !this->socket) {
				this->socket = std::move(socket);
				state.connected = true;
				doRead();
			}
			if (!state.connected) {
				closeSession();
			}
			if (error != asio::error::basic_errors::operation_aborted) {
				doAccept();
			}
		});
	}

	void doRead() {
		asio::async_read(*socket, receivedCommand.asBuffer(), [this](std::error_code ec, auto) {
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
		asio::async_write(*socket, gc->asBuffer(), [this, gc](std::error_code ec, auto) {
			state.canSend = false;
		});
	}
};

#endif /* PEER_SERVERPEER_H_ */
