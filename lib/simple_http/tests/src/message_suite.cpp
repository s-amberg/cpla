#include "message_suite.hpp"

#include "simple_http/header.hpp"
#include "simple_http/request.hpp"
#include "simple_http/response.hpp"
#include "simple_http/status_code.hpp"

#include <cute/cute.h>

#include <sstream>
#include <string>

using namespace std::string_literals;

TEST(a_default_constructed_request_is_serialized_to_the_empty_get_request) {
  auto const request = http::request{};
  auto buffer = std::ostringstream{};

  buffer << request;

  ASSERT_EQUAL("GET / HTTP/1.1\r\n\r\n", buffer.str());
}

TEST(a_get_request_with_a_single_header_is_serialized_to_a_get_request_with_a_crlf_terminated_list_of_a_single_header) {
  auto const request = http::request{}.set<http::header::accept>(http::mime_type::text_html);
  auto buffer = std::ostringstream{};

  buffer << request;

  ASSERT_EQUAL("GET / HTTP/1.1\r\nAccept: text/html\r\n\r\n", buffer.str());
}

TEST(a_get_request_with_multiple_headers_is_serialized_to_a_get_request_with_a_crlf_separated_list_of_headers) {
  auto const request = http::request{}.set<http::header::accept>(http::mime_type::text_html).set<http::header::host>("localhost");
  auto buffer = std::ostringstream{};

  buffer << request;

  ASSERT_EQUAL("GET / HTTP/1.1\r\nAccept: text/html\r\nHost: localhost\r\n\r\n", buffer.str());
}

TEST(a_get_request_with_duplicate_headers_is_serialized_to_a_get_request_with_a_crlf_separated_list_of_headers) {
  auto const request = http::request{}.set<http::header::accept>(http::mime_type::text_html).set<http::header::accept>(http::mime_type::image_bmp);
  auto buffer = std::ostringstream{};

  buffer << request;

  ASSERT_EQUAL("GET / HTTP/1.1\r\nAccept: text/html\r\nAccept: image/bmp\r\n\r\n", buffer.str());
}

TEST(ok_response_serializes_to_simple_ok_response) {
  auto const request = http::response{http::status_code::ok};
  auto buffer = std::ostringstream{};

  buffer << request;

  ASSERT_EQUAL("HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n", buffer.str());
}

TEST(a_response_with_a_body_is_serialized_to_a_response_with_a_body) {
  auto const request = http::response{http::status_code::ok}.body("Hello, World!");
  auto buffer = std::ostringstream{};

  buffer << request;

  ASSERT_EQUAL("HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!", buffer.str());
}

TEST(a_response_with_a_header_is_serialized_to_a_response_with_a_header) {
  auto const request = http::response{http::status_code::ok}.set<http::header::content_type>(http::mime_type::text_html);
  auto buffer = std::ostringstream{};

  buffer << request;

  ASSERT_EQUAL("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 0\r\n\r\n", buffer.str());
}

TEST(a_response_with_a_header_and_a_body_is_serialized_to_a_response_with_a_header_and_a_body) {
  auto const request = http::response{http::status_code::ok}.set<http::header::content_type>(http::mime_type::text_html).body("<html></html>");
  auto buffer = std::ostringstream{};

  buffer << request;

  ASSERT_EQUAL("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 13\r\n\r\n<html></html>", buffer.str());
}

cute::suite make_suite_message_suite() {
  return cute::suite{"MIME Type Suite",
                     {
                         a_default_constructed_request_is_serialized_to_the_empty_get_request,
                         a_get_request_with_a_single_header_is_serialized_to_a_get_request_with_a_crlf_terminated_list_of_a_single_header,
                         a_get_request_with_multiple_headers_is_serialized_to_a_get_request_with_a_crlf_separated_list_of_headers,
                         a_get_request_with_duplicate_headers_is_serialized_to_a_get_request_with_a_crlf_separated_list_of_headers,
                         ok_response_serializes_to_simple_ok_response,
                         a_response_with_a_body_is_serialized_to_a_response_with_a_body,
                         a_response_with_a_header_is_serialized_to_a_response_with_a_header,
                         a_response_with_a_header_and_a_body_is_serialized_to_a_response_with_a_header_and_a_body,
                     }};
}
