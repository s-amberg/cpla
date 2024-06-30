#include "JuliaClient.hpp"

#include <asio.hpp>
#include <asio/use_awaitable.hpp>
#include <asio/use_future.hpp>
#include <simple_http.hpp>
#include <fstream>
#include <iostream>

#include <sstream>
#include <string>

JuliaClient::JuliaClient(asio::io_context &context, std::string ip, unsigned short port) : m_context{context}, m_remote{asio::ip::make_address(ip), port} {}

auto JuliaClient::download_image() -> void {
  connect();
}

auto JuliaClient::connect() -> void {
    m_socket.async_connect(m_remote, [this](asio::error_code ec) {
      if (ec) {
        return;
      }
      send_request();
    });
}

auto JuliaClient::send_request() -> void {
  std::cout << "send request" << '\n';

  auto request = http::request{http::method::get};
  auto request_stream = std::ostringstream{};
  request_stream << request;
    asio::async_write(m_socket, asio::buffer(request_stream.str()), [this](asio::error_code ec, std::size_t length){
      read_response_headers();
    });
}

auto JuliaClient::read_response_headers() -> void {
  std::cout << "read headers" << '\n';

  asio::async_read_until(m_socket, m_transfer_buffer, "\r\n\r\n", [this](asio::error_code ec, std::size_t length) {
    if (ec) {
      return;
    }
    auto response_stream = std::istream{&m_transfer_buffer};
    auto response = http::response{response_stream};

    if (!response.complete()) {
      read_response_body(std::move(response));
    }
    handle_response(std::move(response));
  });

}

auto JuliaClient::read_response_body(http::response response) -> void {
    std::cout << "read body" << '\n';
    auto content_length = response.get<http::header::content_length>();
    auto buffered = m_transfer_buffer.size();

    asio::async_read(m_socket, m_transfer_buffer, asio::transfer_exactly(content_length - buffered), [this, response](asio::error_code ec, std::size_t length) mutable {
      auto response_stream = std::istream{&m_transfer_buffer};
      response.body(response_stream);
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
