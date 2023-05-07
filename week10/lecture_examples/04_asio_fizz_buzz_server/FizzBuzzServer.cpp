#include "FizzBuzz.h"
#include "Server.h"
#include "Session.h"

#include <asio.hpp>


int main() {
	asio::io_context context{};
	Server server{context, 1234};
	context.run();
}

