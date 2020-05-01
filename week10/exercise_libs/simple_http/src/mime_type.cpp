#include "simple_http/mime_type.h"

#include <array>
#include <stdexcept>
#include <string>
#include <utility>

using namespace http;

// @formatter:off
auto constexpr string_map = std::array{
  std::pair{mime_type::image_bmp, "image/bmp"},
  std::pair{mime_type::image_ppm, "image/ppm"},
  std::pair{mime_type::text_html, "text/html"},
};
// @formatter:on
template<>
auto to_string(mime_type const &object) -> std::string {
  auto found = detail::to_string_impl(string_map, object);
  if (found) {
    return *found;
  }

  throw std::invalid_argument{"invalid mime type: " + std::to_string(static_cast<int>(object))};
}

template<>
auto from_string(std::string const &stringified) -> mime_type {
  auto found = detail::from_string_impl(string_map, stringified);
  if (found) {
    return *found;
  }

  throw std::invalid_argument{"invalid mime type: " + stringified};
}
