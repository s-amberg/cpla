#ifndef SESSION_H_
#define SESSION_H_

#include "FizzBuzz.h"

#include <asio.hpp>
#include <cstddef>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>


struct Session : std::enable_shared_from_this<Session> {

	explicit Session(asio::ip::tcp::socket socket) : socket{std::move(socket)} {
		std::cout << "Starting Session for Client " << this->socket.remote_endpoint().address() << ':' << this->socket.remote_endpoint().port() << std::endl;
	}

	void start() {
		read();
	}

private:
	void read() {
		auto readCompletionHandler = [self = shared_from_this()] (asio::error_code ec, std::size_t length) {
			if (ec) {
				std::cout << "Closing session " << ec.message() << std::endl;
				self->socket.close();
				return;
			}

			int number{};
			if (self->input >> number) {
				self->input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				self->write(self->createReply(number));
			}
		};
		asio::async_read_until(socket, buffer, '\n', readCompletionHandler);
	}

	void write(std::string input) {
		auto data = std::make_shared<std::string>(input);
		auto writeCompletionHandler = [self = shared_from_this(), data] (asio::error_code ec, std::size_t length){
			if (ec) {
				std::cout << "Closing session " << ec.message() << std::endl;
				self->socket.close();
				return;
			}
			self->read();
		};
		asio::async_write(socket, asio::buffer(data->c_str(), data->size()), writeCompletionHandler);
	}

	std::string createReply(int number) {
		using namespace std::string_literals;
		std::ostringstream reply{};
		reply << number << ": "s << fizzbuzz(number) << '\n';
		return reply.str();
	}

	asio::streambuf buffer{};
	std::istream input{&buffer};
	asio::ip::tcp::socket socket;
};



#endif /* SESSION_H_ */
