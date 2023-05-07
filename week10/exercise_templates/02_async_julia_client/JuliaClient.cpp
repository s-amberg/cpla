#include "JuliaClient.hpp"

#include <asio.hpp>
#include <simple_http.hpp>

#include <string>

JuliaClient::JuliaClient(asio::io_context &context, std::string ip, unsigned short port) : m_context{context}, m_remote{asio::ip::make_address(ip), port} {}

auto JuliaClient::download_image() -> void {
  // TODO: implement
}

auto JuliaClient::connect() -> void {
  // TODO: implement
}

auto JuliaClient::send_request() -> void {
  // TODO: implement
}

auto JuliaClient::read_response_headers() -> void {
  // TODO: implement
}

auto JuliaClient::read_response_body(http::response response) -> void {
  // TODO: implement
}

auto JuliaClient::handle_response(http::response response) -> void {
  // TODO: implement
}
