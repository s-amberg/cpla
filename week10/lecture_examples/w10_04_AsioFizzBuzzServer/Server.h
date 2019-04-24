#ifndef SERVER_H_
#define SERVER_H_

#include "Session.h"

#include <asio.hpp>
#include <memory>
#include <utility>

struct Server {
	using tcp = asio::ip::tcp;
	Server(asio::io_context & context, unsigned short port)
			: acceptor{context, tcp::endpoint{tcp::v4(), port}}	{
		accept();
	}

private:
	void accept() {
		auto acceptHandler = [this] (asio::error_code ec, tcp::socket peer) {
			if (!ec) {
				auto session = std::make_shared<Session>(std::move(peer));
				session->start();
			}
			accept();
		};
		acceptor.async_accept(acceptHandler);
	}
	tcp::acceptor acceptor;
};


#endif /* SERVER_H_ */
