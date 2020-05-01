#include "message_suite.h"

#include "simple_http/header.h"
#include "simple_http/request.h"
#include "simple_http/response.h"
#include "simple_http/status_code.h"

#include "cute.h"

#include <string>
#include <sstream>

using namespace std::string_literals;

void a_default_constructed_request_is_serialized_to_the_empty_get_request() {
  auto const request = http::request{};
  auto buffer = std::ostringstream{};

  buffer << request;

  ASSERT_EQUAL("GET / HTTP/1.1\r\n\r\n", buffer.str());
}

void a_get_request_with_a_single_header_is_serialized_to_a_get_request_with_a_crlf_terminated_list_of_a_single_header() {
  auto const request = http::request{}.set<http::header::accept>(http::mime_type::text_html);
  auto buffer = std::ostringstream{};

  buffer << request;

  ASSERT_EQUAL("GET / HTTP/1.1\r\nAccept: text/html\r\n\r\n", buffer.str());
}

void a_get_request_with_multiple_headers_is_serialized_to_a_get_request_with_a_crlf_separated_list_of_headers() {
  auto const request = http::request{}.set<http::header::accept>(http::mime_type::text_html).set<http::header::host>("localhost");
  auto buffer = std::ostringstream{};

  buffer << request;

  ASSERT_EQUAL("GET / HTTP/1.1\r\nAccept: text/html\r\nHost: localhost\r\n\r\n", buffer.str());
}

void a_get_request_with_duplicate_headers_is_serialized_to_a_get_request_with_a_crlf_separated_list_of_headers() {
  auto const request = http::request{}.set<http::header::accept>(http::mime_type::text_html).set<http::header::accept>(http::mime_type::image_bmp);
  auto buffer = std::ostringstream{};

  buffer << request;

  ASSERT_EQUAL("GET / HTTP/1.1\r\nAccept: text/html\r\nAccept: image/bmp\r\n\r\n", buffer.str());
}

void ok_response_serializes_to_simple_ok_response() {
  auto const request = http::response{http::status_code::ok};
  auto buffer = std::ostringstream{};

  buffer << request;

  ASSERT_EQUAL("HTTP/1.1 200 OK\r\n\r\n", buffer.str());
}

void a_response_with_a_body_is_serialized_to_a_response_with_a_body() {
  auto const request = http::response{http::status_code::ok}.body("Hello, World!");
  auto buffer = std::ostringstream{};

  buffer << request;

  ASSERT_EQUAL("HTTP/1.1 200 OK\r\n\r\nHello, World!", buffer.str());
}

void a_response_with_a_header_is_serialized_to_a_response_with_a_header() {
  auto const request = http::response{http::status_code::ok}.set<http::header::content_type>(http::mime_type::text_html);
  auto buffer = std::ostringstream{};

  buffer << request;

  ASSERT_EQUAL("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n", buffer.str());
}

void a_response_with_a_header_and_a_body_is_serialized_to_a_response_with_a_header_and_a_body() {
  auto const request = http::response{http::status_code::ok}.set<http::header::content_type>(http::mime_type::text_html).body("<html></html>");
  auto buffer = std::ostringstream{};

  buffer << request;

  ASSERT_EQUAL("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html></html>", buffer.str());
}

cute::suite make_suite_message_suite() {
  cute::suite s{};
  s.push_back(CUTE(a_default_constructed_request_is_serialized_to_the_empty_get_request));
  s.push_back(CUTE(a_get_request_with_a_single_header_is_serialized_to_a_get_request_with_a_crlf_terminated_list_of_a_single_header));
  s.push_back(CUTE(a_get_request_with_multiple_headers_is_serialized_to_a_get_request_with_a_crlf_separated_list_of_headers));
  s.push_back(CUTE(a_get_request_with_duplicate_headers_is_serialized_to_a_get_request_with_a_crlf_separated_list_of_headers));
  s.push_back(CUTE(ok_response_serializes_to_simple_ok_response));
  s.push_back(CUTE(a_response_with_a_body_is_serialized_to_a_response_with_a_body));
  s.push_back(CUTE(a_response_with_a_header_is_serialized_to_a_response_with_a_header));
	s.push_back(CUTE(a_response_with_a_header_and_a_body_is_serialized_to_a_response_with_a_header_and_a_body));
  return s;
}
