#include <array>
#include <cstdlib>
#include <iostream>
#include <string>

#include <asio.hpp>
#include <sstream>

auto run_echo_server(unsigned short port) -> void {
  asio::io_context context{};
  asio::ip::tcp::endpoint localEndpoint{asio::ip::tcp::v4(), port};
  asio::ip::tcp::acceptor acceptor{context, localEndpoint};
  acceptor.set_option(asio::ip::tcp::socket::reuse_address{});

  std::cout << "accepting connections on: " << localEndpoint << std::endl;

  asio::ip::tcp::endpoint peerEndpoint{};
  asio::ip::tcp::socket peerSocket = acceptor.accept(peerEndpoint);

  std::cout << "connection established with: " << peerEndpoint << std::endl;

  do {
    std::string message{};
    asio::error_code errorCode{};
    auto readLength = asio::read_until(peerSocket, asio::dynamic_buffer(message), '\n', errorCode);
    if (errorCode == asio::error::eof) {
      peerSocket.shutdown(asio::ip::tcp::socket::shutdown_both);
      std::cout << "finished" << std::endl;
      return;
    } else if (errorCode) {
      throw asio::system_error{errorCode};
    }
    std::cout << "Data received " << readLength << " byte: ";
    std::cout << message;
    std::cout << std::endl;
    asio::write(peerSocket, asio::buffer(message.c_str(), readLength));
    std::cout << "Reply sent" << std::endl;
  } while (true);
}

auto main(int argc, char const *argv[]) -> int {
  unsigned short port;
  if (argc > 1) {
    port = std::stoul(argv[1], nullptr, 10);
  } else {
    port = 1234;
  }
  try {
    run_echo_server(port);
  } catch (asio::system_error const &e) {
    std::cout << "An error occurred: " << e.what();
  }
}
