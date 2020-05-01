#ifndef INCLUDE_SERVER_H_
#define INCLUDE_SERVER_H_

#include "remote.h"
#include "worker_pool.h"

#include "simple_http/request.h"

#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"

#include <memory>
#include <set>

namespace julia {

struct server : remote::listener {
	server(asio::io_context & context, worker_pool & pool, unsigned short port = 9042);

	~server();

	void start_accepting();
	void stop_accepting();

	void on_disconnect(remote_ptr remote) override;
	void on_request(remote_ptr remote, http::request request) override;

private:
	asio::io_context & m_context;
	asio::ip::tcp::endpoint m_local_endpoint;
	worker_pool & m_pool;

	asio::ip::tcp::acceptor m_acceptor{m_context};
	std::set<std::shared_ptr<remote>> m_remotes{};
};

}

#endif /* INCLUDE_SERVER_H_ */
