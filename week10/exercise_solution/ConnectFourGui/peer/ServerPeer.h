#ifndef PEER_SERVERPEER_H_
#define PEER_SERVERPEER_H_

#include "Peer.h"
#include "GameCommand.hpp"

#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/read.hpp"
#include "asio/write.hpp"

#include <functional>
#include <memory>
#include <system_error>
#include <string>
#include <utility>

struct GameSession: std::enable_shared_from_this<GameSession> {
	GameSession(asio::ip::tcp::socket socket, std::function<void(Column)> callback) :
			socket { std::move(socket) }, callback { callback } {
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
		doSend(gc);
	}

	bool canSend() const {
		return allowedToSend;
	}

private:
	asio::ip::tcp::socket socket;
	std::function<void(Column)> callback;
	GameCommand receivedCommand { };
	bool allowedToSend { };

	void doRead() {
		asio::async_read(socket, receivedCommand.asBuffer(), [this](std::error_code ec, auto) {
			if (!ec) {
				callback(receivedCommand.decode());
				allowedToSend = true;
				doRead();
			}
		});
	}

	void doSend(std::shared_ptr<GameCommand> gc) {
		asio::async_write(socket, gc->asBuffer(), [this, gc](std::error_code ec, auto) {
			allowedToSend = false;
		});
	}
};

struct ServerPeer: Peer {
	ServerPeer(asio::io_context & context, unsigned short port, std::function<void(Column)> callback) :
			acceptor { context, asio::ip::tcp::endpoint { asio::ip::tcp::v4(), port } }, callback { callback } {
	}

	virtual void send(Column column) override {
		if (canSend()) {
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
		session = nullptr;
		std::error_code ignored { };
		acceptor.cancel(ignored);
		acceptor.close(ignored);
	}

	virtual bool canSend() const override {
		return session && session->canSend();
	}

	virtual std::string name() const override {
		return peerName;
	}
private:
	asio::ip::tcp::acceptor acceptor;
	std::function<void(Column)> callback;
	std::shared_ptr<GameSession> session { nullptr };
	std::string const peerName { "Server" };

	void doAccept() {
		acceptor.async_accept([this](std::error_code const error, asio::ip::tcp::socket && socket) {
			if (!error && !session) {
				session = std::make_shared<GameSession>(std::move(socket), callback);
			}
			if (error != asio::error::basic_errors::operation_aborted) {
				doAccept();
			}
		});
	}

};

#endif /* PEER_SERVERPEER_H_ */
