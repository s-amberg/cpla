#include "server.h"
#include "worker_pool.h"

#include "asio/io_context.hpp"

int main()
{
	auto run_loop = asio::io_context{};
	auto workers = worker_pool{4};

	auto server = julia::server{run_loop, workers, 8080};
	server.start_accepting();

	run_loop.run();
}
