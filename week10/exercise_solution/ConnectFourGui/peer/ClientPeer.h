#ifndef PEER_CLIENTPEER_H_
#define PEER_CLIENTPEER_H_

#include "Peer.h"
#include "GameCommand.hpp"

#include "asio/connect.hpp"
#include "asio/write.hpp"
#include "asio/read.hpp"
#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/post.hpp"

#include <charconv>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
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
		if (socket.is_open()) {
			std::error_code ignored { };
			socket.shutdown(asio::ip::tcp::socket::shutdown_both, ignored);
			socket.close(ignored);
		}
	}

	virtual void restart() override {
		disconnect();
		connect();
	}

	virtual bool canSend() const override {
		return allowedToSend;
	}

	virtual std::string name() const override {
		return peerName;
	}
private:
	asio::ip::tcp::socket socket;
	asio::ip::tcp::resolver::results_type const endpoints;
	std::function<void(Column)> callback;
	GameCommand receivedCommand { };
	bool allowedToSend { };
	std::string const peerName { "Client" };

	void doConnect() {
		asio::async_connect(socket, endpoints, [this](std::error_code ec, auto)
		{
			if (!ec)
			{
				allowedToSend = true;
				doRead();
			}
		});
	}

	void doRead() {
		asio::async_read(socket, receivedCommand.asBuffer(), [this](std::error_code ec, auto) {
			if (!ec) {
				callback(receivedCommand.decode());
				allowedToSend = true;
				doRead();
			} else {
				disconnect();
			}
		});
	}

	void doSend(std::shared_ptr<GameCommand> gc) {
		asio::async_write(socket, gc->asBuffer(), [this, gc](std::error_code ec, auto) {
			allowedToSend = false;
			if (ec) {
				disconnect();
			}
		});
	}
};

#endif /* PEER_CLIENTPEER_H_ */
