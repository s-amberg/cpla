#include "server.h"

#include "bmp.h"
#include "julia.h"
#include "remote.h"
#include "worker_pool.h"

#include "simple_http/disposition.h"
#include "simple_http/request.h"
#include "simple_http/response.h"
#include "simple_http/status_code.h"

#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <string>
#include <utility>

namespace julia {

server::server(asio::io_context &context, worker_pool &pool, unsigned short port) :
		m_context { context }, m_local_endpoint { asio::ip::tcp::v4(), port }, m_pool { pool } {
	m_acceptor.open(m_local_endpoint.protocol());
	m_acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
	m_acceptor.bind(m_local_endpoint);
	m_acceptor.listen();
}

server::~server() {
	stop_accepting();
	for_each(begin(m_remotes), end(m_remotes), [](auto remote) {
		remote->close();
	});
}

void server::start_accepting() {
	m_acceptor.async_accept(m_context, [this](auto const &error, auto peer) {
		if (!error) {
			auto inserted = m_remotes.insert(make_remote(std::move(peer)));
			if (inserted.second) {
				auto &remote = *inserted.first;
				remote->add(*this);
				remote->start();
			}
			start_accepting();
		}
	});
}

void server::stop_accepting() {
	m_acceptor.cancel();
}

//"Content-Disposition: inline; filename=%s\r\n"

void server::on_disconnect(remote_ptr remote) {
	m_remotes.erase(remote);
	remote->remove(*this);
	remote->close();
}

void server::on_request(remote_ptr remote, http::request request) {
	if(request.path() != "/") {
		remote->send(http::response{http::status_code::not_found});
		return;
	}

	try {
		auto const exponent = std::stod(request.parameter("exponent").value_or("2"));
		auto const imaginary = std::stod(request.parameter("k_imaginary").value_or("-1"));
		auto const iterations = std::stoul(request.parameter("iterations").value_or("800"));
		auto const real = std::stod(request.parameter("k_real").value_or("0"));
		auto const size = std::stoul(request.parameter("size").value_or("800"));

		m_pool.submit([=, remote = std::move(remote)] {
			auto image = julia::bmp {static_cast<std::uint32_t>(size)};
			julia::render(image, { {0, 0}, 1}, exponent, {real, imaginary}, iterations);
			auto data = image.dump();

			auto response = http::response{http::status_code::ok}
				.set<http::header::content_type>(http::mime_type::image_bmp)
				.set<http::header::content_disposition>(http::disposition::inline_)
				.body(data);
			remote->send(response);
		});
	} catch (std::invalid_argument const &e) {
		remote->send(http::response {http::status_code::bad_request}.body(e.what()));
	} catch (...) {
		remote->send(http::response {http::status_code::internal_server_error}.body("500 Internal Server Error"));
	}
}

}
