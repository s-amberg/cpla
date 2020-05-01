#ifndef INCLUDE_REMOTE_H_
#define INCLUDE_REMOTE_H_

#include "simple_http/request.h"
#include "simple_http/response.h"

#include "asio/ip/tcp.hpp"
#include "asio/strand.hpp"
#include "asio/streambuf.hpp"

#include <memory>
#include <queue>
#include <vector>
#include <functional>
#include <string>

namespace julia {

using remote_ptr = std::shared_ptr<struct remote>;

struct remote: std::enable_shared_from_this<remote> {
	struct listener {
		virtual ~listener() = default;

		virtual void on_disconnect(remote_ptr remote);
		virtual void on_request(remote_ptr remote, http::request request);
	};

	void start();
	void close();

	void send(http::response response);

	void add(listener & listener);
	void remove(listener & listener);

	asio::ip::tcp::endpoint endpoint() const;

protected:
	explicit remote(asio::ip::tcp::socket peer);

private:
	void notify_disconnect();
	void notify_request(http::request request);

	void do_transmit();
	void do_receive_header();
	void do_receive_body(http::request request);

	asio::ip::tcp::socket m_peer;
	asio::strand<asio::ip::tcp::socket::executor_type> m_strand;

	std::vector<std::reference_wrapper<listener>> m_listeners{};
	asio::streambuf m_receive_buffer{};
	std::queue<http::response> m_response_queue{};
	std::string m_transmission_buffer{};
};

remote_ptr make_remote(asio::ip::tcp::socket peer);

}

#endif /* INCLUDE_REMOTE_H_ */
