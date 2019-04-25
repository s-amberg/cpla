#ifndef PEER_CLIENTPEER_H_
#define PEER_CLIENTPEER_H_

#include "Peer.h"

#include "../game/GameCommand.hpp"
#include "../game/Board.h"

#include "../state/PeerState.hpp"

#include "asio/connect.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/io_context.hpp"
#include "asio/post.hpp"
#include "asio/read.hpp"
#include "asio/write.hpp"

#include <atomic>
#include <functional>
#include <memory>
#include <system_error>

struct ClientPeer: Peer {
	ClientPeer(asio::io_context & context, asio::ip::tcp::resolver::results_type const & endpoints, std::function<void(Column)> callback) :
			socket { context }, endpoints { endpoints }, callback { callback } {
	}

	virtual void send(Column column) override {
		asio::post(socket.get_executor().context(), [this, column]()
		{
			doSend(std::make_shared<GameCommand>(column));
		});
	}

	virtual void connect() override {
		doConnect();
	}

	virtual void disconnect() override {
		allowedToSend = false;
		isConnected = false;
		if (socket.is_open()) {
			std::error_code ignored { };
			socket.shutdown(asio::ip::tcp::socket::shutdown_both, ignored);
			socket.close(ignored);
		}
	}

	virtual PeerState peerState() override {
		return state;
	}
private:
	asio::ip::tcp::socket socket;
	asio::ip::tcp::resolver::results_type const endpoints;
	std::function<void(Column)> callback;
	GameCommand receivedCommand { };
	std::atomic_bool allowedToSend { };
	std::atomic_bool isConnected { };
	PeerState state { //
		"Client", //
		[this] () -> bool { return allowedToSend; }, //
		[this] () -> bool { return isConnected; }, //
		ConnectFour::Player::Red //
	};

	void reConnect(std::error_code error) {
		if (error != asio::error::basic_errors::operation_aborted) {
			doConnect();
		}
	}

	void doConnect() {
		asio::async_connect(socket, endpoints, [this](std::error_code error, auto)
		{
			if (!error)
			{
				allowedToSend = true;
				isConnected = true;
				doRead();
			} else {
				reConnect(error);
			}
		});
	}

	void doRead() {
		asio::async_read(socket, receivedCommand.asBuffer(), [this](std::error_code error, auto) {
			if (!error) {
				callback(receivedCommand.decode());
				allowedToSend = true;
				doRead();
			} else {
				disconnect();
				reConnect(error);
			}
		});
	}

	void doSend(std::shared_ptr<GameCommand> gc) {
		asio::async_write(socket, gc->asBuffer(), [this, gc](std::error_code error, auto) {
			allowedToSend = false;
			if (error) {
				disconnect();
			}
		});
	}
};

#endif /* PEER_CLIENTPEER_H_ */
