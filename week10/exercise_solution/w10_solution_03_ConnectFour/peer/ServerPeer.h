#ifndef PEER_SERVERPEER_H_
#define PEER_SERVERPEER_H_

#include "Board.h"
#include "Peer.h"
#include "GameCommand.hpp"
#include "GameSession.hpp"

#include "ConnectFour.h"

#include "asio/error.hpp"
#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"

#include <functional>
#include <memory>
#include <system_error>
#include <string>
#include <utility>

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
