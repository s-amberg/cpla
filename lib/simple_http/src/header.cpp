#include "simple_http/header.hpp"

#include <array>
#include <stdexcept>
#include <string>
#include <utility>

using namespace http;

unknown_header::unknown_header(std::string name)
    : std::invalid_argument{"unknown header name: " + name} {
}

// @formatter:off
    auto constexpr string_map = std::array {
      std::pair {header::accept, "Accept"},
      std::pair {header::host, "Host"},
      std::pair {header::content_type, "Content-Type"},
      std::pair {header::content_length, "Content-Length"},
      std::pair {header::content_disposition, "Content-Disposition"},
      std::pair {header::connection, "Connection"},
    };
// @formatter:on
template<>
auto to_string(header const &object) -> std::string {
  auto found = detail::to_string_impl(string_map, object);
  if (found) {
    return *found;
  }

  throw std::invalid_argument{"invalid header: " + std::to_string(static_cast<int>(object))};
}

template<>
auto from_string(std::string const &stringified) -> header {
  auto found = detail::from_string_impl(string_map, stringified);
  if (found) {
    return *found;
  }

  throw unknown_header{stringified};
}
