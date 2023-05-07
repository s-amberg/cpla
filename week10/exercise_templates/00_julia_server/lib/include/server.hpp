#ifndef INCLUDE_SERVER_H_
#define INCLUDE_SERVER_H_

#include "remote.hpp"
#include "worker_pool.hpp"

#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <simple_http/request.hpp>

#include <memory>
#include <set>

namespace julia {

struct server : remote::listener {
  server(asio::io_context &context, worker_pool &pool, unsigned short port = 9042);

  ~server() override;

  auto start_accepting() -> void;
  auto stop_accepting() -> void;

  auto on_disconnect(remote_ptr remote) -> void override;
  auto on_request(remote_ptr remote, http::request request) -> void override;

private:
  asio::io_context &m_context;
  asio::ip::tcp::endpoint m_local_endpoint;
  worker_pool &m_pool;

  asio::ip::tcp::acceptor m_acceptor{m_context};
  std::set<std::shared_ptr<remote>> m_remotes{};
};

} // namespace julia

#endif /* INCLUDE_SERVER_H_ */
