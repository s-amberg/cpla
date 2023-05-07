#include <asio.hpp>
#include <simple_http.hpp>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>

auto main() -> int {
  auto context = asio::io_context{};

  auto server_address = asio::ip::make_address("127.0.0.1");
  auto server_endpoint = asio::ip::tcp::endpoint{server_address, 8080};
  auto socket = asio::ip::tcp::socket{context};
  socket.connect(server_endpoint);

  auto transfer_buffer = asio::streambuf{};

  auto request = std::ostream{&transfer_buffer};
  request << http::request{http::method::get};

  asio::write(socket, transfer_buffer);

  asio::read_until(socket, transfer_buffer, "\r\n\r\n");
  auto response_stream = std::istream{&transfer_buffer};

  auto response = http::response{response_stream};

  if (!response.complete()) {
    auto content_length = response.get<http::header::content_length>();
    auto buffered = transfer_buffer.size();
    asio::read(socket, transfer_buffer, asio::transfer_exactly(content_length - buffered));
    response.body(response_stream);
  }

  if (response.status() != http::status_code::ok) {
    std::cerr << "Server did not accept the request: " << to_string(response.status()) << '\n';
    return EXIT_FAILURE;
  }

  auto file = std::ofstream{"julia.bmp", std::ios::trunc | std::ios::binary};
  auto image_data = response.body();
  copy(cbegin(image_data), cend(image_data), std::ostream_iterator<char>{file});
  file.close();

  std::cout << "Successfully received Julia fractal from the server. Result is in julia.bmp\n";
}
