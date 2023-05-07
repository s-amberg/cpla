#include "JuliaClient.hpp"

#include <asio.hpp>
#include <simple_http.hpp>

#include <algorithm>
#include <fstream>
#include <istream>
#include <iterator>
#include <string>
#include <utility>

JuliaClient::JuliaClient(asio::io_context &context, std::string ip, unsigned short port) : m_context{context}, m_remote{asio::ip::make_address(ip), port} {}

auto JuliaClient::download_image() -> void {
  connect();
}

auto JuliaClient::connect() -> void {
  m_socket.async_connect(m_remote, [&](auto error) {
    if (!error) {
      send_request();
    }
  });
}

auto JuliaClient::send_request() -> void {
  auto request = http::request{http::method::get};
  auto request_stream = std::ostream{&m_transfer_buffer};
  request_stream << request;
  asio::async_write(m_socket, m_transfer_buffer, [this](auto error, auto) {
    if (!error) {
      read_response_headers();
    }
  });
}

auto JuliaClient::read_response_headers() -> void {
  asio::async_read_until(m_socket, m_transfer_buffer, "\r\n\r\n", [this](auto error, auto) {
    if (error) {
      return;
    }

    auto response_stream = std::istream{&m_transfer_buffer};
    auto response = http::response{response_stream};
    if (response.complete()) {
      handle_response(std::move(response));
    } else {
      read_response_body(std::move(response));
    }
  });
}

auto JuliaClient::read_response_body(http::response response) -> void {
  auto remainder = response.get<http::header::content_length>() - m_transfer_buffer.size();
  asio::async_read(m_socket, m_transfer_buffer, asio::transfer_exactly(remainder), [response, this](auto error, auto) mutable {
    auto body_stream = std::istream(&m_transfer_buffer);
    response.body(body_stream);
    handle_response(std::move(response));
  });
}

auto JuliaClient::handle_response(http::response response) -> void {
  if (response.status() == http::status_code::ok) {
    auto file = std::ofstream{"julia.bmp", std::ios::trunc | std::ios::binary};
    auto image_data = response.body();
    copy(cbegin(image_data), cend(image_data), std::ostream_iterator<char>{file, ""});
  }
}
