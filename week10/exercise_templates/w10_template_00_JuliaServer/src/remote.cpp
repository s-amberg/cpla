#include "remote.h"

#include "simple_http/request.h"
#include "simple_http/response.h"

#include "asio/bind_executor.hpp"
#include "asio/buffer.hpp"
#include "asio/completion_condition.hpp"
#include "asio/error.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/post.hpp"
#include "asio/read.hpp"
#include "asio/read_until.hpp"
#include "asio/write.hpp"

#include <algorithm>
#include <functional>
#include <istream>
#include <iterator>
#include <memory>
#include <sstream>
#include <utility>

namespace julia {

struct ctor_access: remote {
	template<typename ...ParamTypes>
	explicit ctor_access(ParamTypes &&... args) :
			remote { std::forward<ParamTypes>(args)... } {

	}
};

remote_ptr make_remote(asio::ip::tcp::socket peer) {
	return std::make_shared<ctor_access>(std::move(peer));
}

remote::remote(asio::ip::tcp::socket peer) :
		m_peer { std::move(peer) }, m_strand { asio::make_strand(peer.get_executor()) } {
}

void remote::start() {
	do_receive_header();
}

void remote::close() {
	asio::post(m_strand, [this, that = shared_from_this()] {
		auto ignored = asio::error_code{};
		m_peer.shutdown(asio::ip::tcp::socket::shutdown_both, ignored);
		m_peer.close(ignored);
	});
}

void remote::send(http::response response) {
	asio::post(m_strand, [this, that = shared_from_this(), response = std::move(response)] {
		m_response_queue.push(std::move(response));
		if(m_response_queue.size() == 1) {
			do_transmit();
		}
	});
}

void remote::add(listener &listener) {
	asio::post(m_strand, [this, that = shared_from_this(), &listener] {
		m_listeners.push_back(std::ref(listener));
	});
}

void remote::remove(listener &listener) {
	asio::post(m_strand, [this, that = shared_from_this(), &listener] {
		auto const new_end = remove_if(begin(m_listeners), end(m_listeners), [&](auto entry) {
					return &entry.get() == &listener;
				});
		m_listeners.erase(new_end, end(m_listeners));
	});
}

asio::ip::tcp::endpoint remote::endpoint() const {
	return m_peer.remote_endpoint();
}

void remote::notify_disconnect() {
	for_each(begin(m_listeners), end(m_listeners), [&](auto listener) {
		listener.get().on_disconnect(shared_from_this());
	});
}

void remote::notify_request(http::request request) {
	for_each(begin(m_listeners), end(m_listeners), [&](auto listener) {
		listener.get().on_request(shared_from_this(), request);
	});
}

void remote::do_transmit() {
	auto data = std::ostringstream { };
	data << m_response_queue.front();
	m_transmission_buffer = data.str();
	asio::async_write(m_peer, asio::buffer(m_transmission_buffer),
			asio::bind_executor(m_strand, [this, that = shared_from_this()](auto const &error, auto) {
				m_response_queue.pop();
				if (!error) {
					if (!m_response_queue.empty()) {
						do_transmit();
					}
				} else if (error == asio::error::operation_aborted || error == asio::error::connection_reset) {
					notify_disconnect();
				}
			}));
}

void remote::do_receive_header() {
	asio::async_read_until(m_peer, m_receive_buffer, "\r\n\r\n",
			asio::bind_executor(m_strand, [this, that = shared_from_this()](auto const &error, auto) {
				if (error == asio::error::eof || error == asio::error::connection_reset) {
					notify_disconnect();
					return;
				} else if (error == asio::error::operation_aborted) {
					return;
				}

				auto stream = std::istream(&m_receive_buffer);
				auto request = http::request { };
				try {
					request.read_headers(stream);

					if (request.has(http::header::content_length)) {
						do_receive_body(std::move(request));
					} else {
						notify_request(std::move(request));
						do_receive_header();
					}
				} catch (...) {
					close();
				}
			}));
}

void remote::do_receive_body(http::request request) {
	auto body_size = request.get<http::header::content_length>();
	asio::async_read(m_peer, m_receive_buffer, asio::transfer_exactly(body_size),
			asio::bind_executor(m_strand, [this, that = shared_from_this(), request = std::move(request)](auto const &error, auto) mutable {
				if (error == asio::error::eof || error == asio::error::connection_reset) {
					notify_disconnect();
					return;
				} else if (error == asio::error::operation_aborted) {
					return;
				}

				auto buffers = m_receive_buffer.data();
				auto begin = asio::buffers_begin(buffers);
				auto end = begin + m_receive_buffer.size();
				request.body( std::string{ begin, end });
				m_receive_buffer.consume(m_receive_buffer.size());
				notify_request(std::move(request));
				do_receive_header();
			}));
}

void remote::listener::on_disconnect(remote_ptr) {
}

void remote::listener::on_request(remote_ptr, http::request) {
}

}
