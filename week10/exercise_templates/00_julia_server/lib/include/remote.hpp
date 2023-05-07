#ifndef INCLUDE_REMOTE_H_
#define INCLUDE_REMOTE_H_

#include <asio/ip/tcp.hpp>
#include <asio/strand.hpp>
#include <asio/streambuf.hpp>
#include <simple_http/request.hpp>
#include <simple_http/response.hpp>

#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <vector>

namespace julia {

using remote_ptr = std::shared_ptr<struct remote>;

struct remote : std::enable_shared_from_this<remote> {
  struct listener {
    virtual ~listener() = default;

    virtual auto on_disconnect(remote_ptr remote) -> void;
    virtual auto on_request(remote_ptr remote, http::request request) -> void;
  };

  auto start() -> void;
  auto close() -> void;

  auto send(http::response response) -> void;

  auto add(listener &listener) -> void;
  auto remove(listener &listener) -> void;

  auto endpoint() const -> asio::ip::tcp::endpoint;

protected:
  explicit remote(asio::ip::tcp::socket peer);

private:
  auto notify_disconnect() -> void;
  auto notify_request(http::request request) -> void;

  auto do_transmit() -> void;
  auto do_receive_header() -> void;
  auto do_receive_body(http::request request) -> void;

  asio::ip::tcp::socket m_peer;
  asio::strand<asio::ip::tcp::socket::executor_type> m_strand;

  std::vector<std::reference_wrapper<listener>> m_listeners{};
  asio::streambuf m_receive_buffer{};
  std::queue<http::response> m_response_queue{};
  std::string m_transmission_buffer{};
};

auto make_remote(asio::ip::tcp::socket peer) -> remote_ptr;

} // namespace julia

#endif /* INCLUDE_REMOTE_H_ */
