#ifndef JULIACLIENT_H_
#define JULIACLIENT_H_

#include "simple_http.h"
#include "asio.hpp"

#include <string>

struct JuliaClient {
	JuliaClient(asio::io_context &context, std::string ip, unsigned short port);

	void download_image();

private:
	void connect();
	void send_request();
	void read_response_headers();
	void read_response_body(http::response response);
	void handle_response(http::response response);

	asio::io_context &m_context;
	asio::ip::tcp::endpoint m_remote;

	asio::ip::tcp::socket m_socket { m_context };
	asio::streambuf m_transfer_buffer { };
};

#endif /* JULIACLIENT_H_ */
