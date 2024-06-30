#include <asio.hpp>
#include <asio/completion_condition.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/streambuf.hpp>
#include <iostream>
#include <simple_http.hpp>
#include <fstream>
#include <iterator>
#include <sstream>

auto read_image(asio::ip::tcp::socket socket) -> void {
    constexpr size_t bufferSize= 1024;
    std::array<char, bufferSize> reply{};
    asio::error_code errorCode{};
    std::ofstream file{};
    std::ostream_iterator<char> out{file};

    file.open("julia.bmp", std::ios::out);
    while(auto state = true) {
        try {
            auto readLength= asio::read(socket, asio::buffer(reply.data(), bufferSize), errorCode);
            std::copy(reply.begin(), reply.begin() + readLength, out);
        } catch (asio::system_error e){
            file.close();
            break;
        }
    }
}

auto main() -> int {
    asio::io_context context{};
    asio::ip::tcp::socket socket{context};

    auto address = asio::ip::make_address("127.0.0.1");
    auto endpoint = asio::ip::tcp::endpoint(address, 8080);
    socket.connect(endpoint);

    
    auto request = std::ostringstream{};
    request << http::request{http::method::get};
    auto writeLen = asio::write(socket, asio::buffer(request.str()));

    constexpr size_t bufferSize= 4024;
    
    asio::error_code errorCode{};
    asio::error_code defaultError{};
    std::ofstream file{"julia.bmp", std::ios::trunc | std::ios::binary};
    std::ostream_iterator<char> out{file};

    std::cout << "wrote" << writeLen << '\n';
    
    // while(errorCode == defaultError) {
        try {
            auto transfer_buffer = asio::streambuf{};

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

            auto body = response.body();

            std::cout << "body length: " << body.length() <<'\n';

            std::ranges::copy(body, out);

            

        } catch (asio::system_error e){
            std::cout << "error: " << e.what() << '\n';

            file.close();
            return 1;
        }
    // }

    return 0;
}



