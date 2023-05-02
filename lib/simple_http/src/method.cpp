#include "simple_http/method.hpp"

#include <array>
#include <stdexcept>
#include <string>
#include <utility>

using namespace http;

// @formatter:off
auto constexpr string_map = std::array{
    std::pair{method::get, "GET"},
    std::pair{method::put, "PUT"},
    std::pair{method::post, "POST"},
    std::pair{method::delete_, "DELETE"},
    std::pair{method::update, "UPDATE"},
};
// @formatter:on
template<>
auto to_string(method const &object) -> std::string {
  auto found = detail::to_string_impl(string_map, object);
  if (found) {
    return *found;
  }

  throw std::invalid_argument{"invalid method: " + std::to_string(static_cast<int>(object))};
}

template<>
auto from_string(std::string const &stringified) -> method {
  auto found = detail::from_string_impl(string_map, stringified);
  if (found) {
    return *found;
  }

  throw std::invalid_argument{"invalid method: " + stringified};
}
