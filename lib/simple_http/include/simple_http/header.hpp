#ifndef INCLUDE_SIMPLE_HTTP_HEADER_H_
#define INCLUDE_SIMPLE_HTTP_HEADER_H_

#include "simple_http/detail/to_string.hpp"

#include <string>
#include <stdexcept>

namespace http {

  enum struct header {
    accept,
    host,
    content_type,
    content_length,
    content_disposition,
    connection,
  };

  struct unknown_header : std::invalid_argument
  {
    explicit unknown_header(std::string name);
  };

}

template<>
auto to_string(http::header const &object) -> std::string;

template<>
auto from_string(std::string const &stringified) -> http::header;

#endif /* INCLUDE_SIMPLE_HTTP_HEADER_H_ */
