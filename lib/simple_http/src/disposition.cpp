#include "simple_http/disposition.hpp"

#include <array>
#include <stdexcept>
#include <string>
#include <utility>

using namespace http;

// @formatter:off
auto constexpr string_map = std::array{
    std::pair{disposition::attachment, "attachment"},
    std::pair{disposition::inline_, "inline"},
};
// @formatter:on
template<>
auto to_string(disposition const &object) -> std::string {
  auto found = detail::to_string_impl(string_map, object);
  if (found) {
    return *found;
  }

  throw std::invalid_argument{"invalid disposition: " + std::to_string(static_cast<int>(object))};
}

template<>
auto from_string(std::string const &stringified) -> disposition {
  auto found = detail::from_string_impl(string_map, stringified);
  if (found) {
    return *found;
  }

  throw std::invalid_argument{"invalid disposition: " + stringified};
}
