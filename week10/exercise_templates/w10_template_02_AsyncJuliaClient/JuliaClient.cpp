#include "JuliaClient.h"

#include "simple_http.h"
#include "asio.hpp"

#include <string>

JuliaClient::JuliaClient(asio::io_context &context, std::string ip, unsigned short port) :
		m_context { context }, m_remote { asio::ip::make_address(ip), port } {
}

void JuliaClient::download_image() {
	// TODO: implement
}

void JuliaClient::connect() {
	// TODO: implement
}

void JuliaClient::send_request() {
	// TODO: implement
}

void JuliaClient::read_response_headers() {
	// TODO: implement
}

void JuliaClient::read_response_body(http::response response) {
	// TODO: implement
}

void JuliaClient::handle_response(http::response response) {
	// TODO: implement
}
