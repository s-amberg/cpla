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
#include "asio/steady_timer.hpp"
#include "asio/write.hpp"

#include <chrono>
#include <functional>
#include <memory>
#include <optional>
#include <system_error>
#include <utility>

struct ServerPeer: Peer {
	ServerPeer(asio::io_context & context, unsigned short port, std::function<void(Column)> callback)
		: endpoint { asio::ip::tcp::v4(), port }
		, acceptor { context, endpoint }
		, restartTimer { context }
		, callback { callback }
		, state { "Server", ConnectFour::Player::Yellow }
	{

	}

	virtual void send(Column column) override {
		if (state.canSend) {
			doSend(std::make_shared<GameCommand>(column));
		}
	}

	virtual void start() override {
		if (!acceptor.is_open()) {
			acceptor.open(endpoint.protocol());
			acceptor.bind(endpoint);
			acceptor.listen();
		}
		doAccept();
	}

	virtual void stop() override {
		stopAccepting();
		closeConnection();
	}

	virtual PeerState const & peerState() const override {
		return state;
	}

private:
	asio::ip::tcp::endpoint endpoint;
	asio::ip::tcp::acceptor acceptor;
	asio::steady_timer restartTimer;

	std::function<void(Column)> const callback;
	PeerState state;

	std::optional<asio::ip::tcp::socket> socket { };
	GameCommand receivedCommand { };

	constexpr static std::chrono::seconds restartInterval { 1 };

	void stopAccepting() {
		std::error_code ignored { };
		acceptor.cancel(ignored);
		acceptor.close(ignored);
	}

	void closeConnection() {
		if(socket) {
			asio::error_code ignored{};
			socket->shutdown(asio::ip::tcp::socket::shutdown_both, ignored);
			socket->close(ignored);
			socket.reset();
		}
		state.connected = false;
		state.canSend = false;
	}

	void doAccept() {
		acceptor.async_accept([this](auto const error, auto socket) {
			if (!error && !this->socket) {
				this->socket = std::move(socket);
				state.connected = true;
				stopAccepting();
				doRead();
			}
		});
	}

	void doRead() {
		asio::async_read(socket.value(), receivedCommand.asBuffer(), [this](auto error, auto) {
			if (!error) {
				callback(receivedCommand.decode());
				state.canSend = true;
				doRead();
			} else if (error == asio::error::eof) {
				closeConnection();
				restart();
			} else {
				stop();
			}
		});
	}

	void restart() {
		restartTimer.expires_after(restartInterval);
		restartTimer.async_wait([this](auto error) {
			if (!error) {
				start();
			}
		});
	}

	void doSend(std::shared_ptr<GameCommand> gc) {
		asio::async_write(socket.value(), gc->asBuffer(), [this, gc](auto const error, auto) {
			if (!error) {
				state.canSend = false;
			} else if (error == asio::error::eof ){
				closeConnection();
				restart();
			} else {
				stop();
			}
		});
	}
};

#endif /* PEER_SERVERPEER_H_ */
