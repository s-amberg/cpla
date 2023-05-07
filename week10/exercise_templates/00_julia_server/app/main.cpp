#include "server.hpp"
#include "worker_pool.hpp"

#include <asio/io_context.hpp>
#include <asio/signal_set.hpp>

#include <csignal>

auto main() -> int {
  auto context = asio::io_context{};
  auto workers = worker_pool{4};

  auto server = julia::server{context, workers, 8080};
  server.start_accepting();

  auto signals = asio::signal_set{context, SIGINT, SIGTERM};
  signals.async_wait([&](auto error, auto) {
    if (!error) {
      server.stop_accepting();
    }
  });

  context.run();
}
