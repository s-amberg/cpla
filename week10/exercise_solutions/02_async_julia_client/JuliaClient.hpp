#ifndef JULIACLIENT_H_
#define JULIACLIENT_H_

#include <asio.hpp>
#include <simple_http.hpp>

#include <string>

struct JuliaClient {
  JuliaClient(asio::io_context &context, std::string ip, unsigned short port);

  auto download_image() -> void;

private:
  auto connect() -> void;
  auto send_request() -> void;
  auto read_response_headers() -> void;
  auto read_response_body(http::response response) -> void;
  auto handle_response(http::response response) -> void;

  asio::io_context &m_context;
  asio::ip::tcp::endpoint m_remote;

  asio::ip::tcp::socket m_socket{m_context};
  asio::streambuf m_transfer_buffer{};
};

#endif /* JULIACLIENT_H_ */
