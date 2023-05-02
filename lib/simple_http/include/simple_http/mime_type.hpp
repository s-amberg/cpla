#ifndef SIMPLE_HTTP_MIME_TYPE_H_
#define SIMPLE_HTTP_MIME_TYPE_H_

#include "simple_http/detail/to_string.hpp"

#include <string>

namespace http {

  enum struct mime_type {
    image_bmp,
    image_ppm,
    text_html,
  };

}

template<>
auto to_string(http::mime_type const &object) -> std::string;

template<>
auto from_string(std::string const &stringified) -> http::mime_type;

#endif /* SIMPLE_HTTP_MIME_TYPE_H_ */
