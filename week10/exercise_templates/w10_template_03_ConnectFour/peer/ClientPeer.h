#ifndef PEER_CLIENTPEER_H_
#define PEER_CLIENTPEER_H_

#include "Peer.h"

#include "../game/GameCommand.hpp"
#include "../game/Board.h"

#include "../state/PeerState.hpp"

#include "asio/connect.hpp"
#include "asio/steady_timer.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/io_context.hpp"
#include "asio/post.hpp"
#include "asio/read.hpp"
#include "asio/write.hpp"

#include <chrono>
#include <functional>
#include <memory>
#include <system_error>

struct ClientPeer: Peer {
	ClientPeer(asio::io_context & context, asio::ip::tcp::resolver::results_type const & endpoints, std::function<void(Column)> callback)
		: socket { context }
	    , endpoints { endpoints }
		, timer { context }
		, callback { callback }
		, state { "Client", ConnectFour::Player::Red } {
	}

	virtual void send(Column column) override {
		doSend(std::make_shared<GameCommand>(column));
	}

	virtual void start() override {
		doConnect();
	}

	virtual void stop() override {
		timer.cancel();
		closeConnection();
	}

	virtual PeerState const & peerState() const override {
		return state;
	}
private:
	constexpr static std::chrono::seconds reconnectTimeout { 2 };
	asio::ip::tcp::socket socket;
	asio::ip::tcp::resolver::results_type const endpoints;
	asio::steady_timer timer;

	std::function<void(Column)> callback;
	PeerState state;

	GameCommand receivedCommand { };

	void reconnect() {
		timer.expires_after(reconnectTimeout);
		timer.async_wait([this](auto error) {
			if (!error) {
				doConnect();
			}
		});
	}

	void closeConnection() {
		state.canSend = false;
		state.connected = false;
		if (socket.is_open()) {
			std::error_code ignored { };
			socket.shutdown(asio::ip::tcp::socket::shutdown_both, ignored);
			socket.close(ignored);
		}
	}

	void doConnect() {
		asio::async_connect(socket, endpoints, [this](auto const error, auto) {
			if (!error) {
				state.canSend = true;
				state.connected = true;
				doRead();
			} else if (error != asio::error::operation_aborted) {
				reconnect();
			} else {
				stop();
			}
		});
	}

	void doRead() {
		asio::async_read(socket, receivedCommand.asBuffer(), [this](auto const error, auto) {
			if (!error) {
				callback(receivedCommand.decode());
				state.canSend = true;
				doRead();
			} else if (error == asio::error::eof) {
				closeConnection();
				reconnect();
			} else {
				stop();
			}
		});
	}

	void doSend(std::shared_ptr<GameCommand> gc) {
		asio::async_write(socket, gc->asBuffer(), [this, gc](std::error_code error, auto) {
			if(!error) {
				state.canSend = false;
			} else if (error == asio::error::eof) {
				closeConnection();
				reconnect();
			} else {
				stop();
			}
		});
	}

};

#endif /* PEER_CLIENTPEER_H_ */
