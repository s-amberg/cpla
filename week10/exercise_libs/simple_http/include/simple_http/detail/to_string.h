#ifndef SIMPLE_HTTP_DETAIL_TO_STRING_H_
#define SIMPLE_HTTP_DETAIL_TO_STRING_H_

#include <array>
#include <cstddef>
#include <string>
#include <utility>
#include <algorithm>
#include <optional>
#include <iterator>

namespace http::detail {

  template<typename ValueType, std::size_t NumberOfEntries>
  auto to_string_impl(std::array<std::pair<ValueType, char const*>, NumberOfEntries> const &string_map, ValueType const &object) ->
      std::optional<std::string> {
    auto found = std::find_if(std::cbegin(string_map), std::cend(string_map), [&](auto entry) {
      return entry.first == object;
    });

    if (found == std::cend(string_map)) {
      return std::nullopt;
    }

    return found->second;
  }

  template<typename ValueType, std::size_t NumberOfEntries>
  auto from_string_impl(std::array<std::pair<ValueType, char const*>, NumberOfEntries> string_map, std::string const &stringified) ->
      std::optional<ValueType> {
    auto found = std::find_if(std::cbegin(string_map), std::cend(string_map), [&](auto entry) {
      return entry.second == stringified;
    });

    if (found == std::cend(string_map)) {
      return std::nullopt;
    }

    return found->first;
  }

}

template<typename ValueType>
auto to_string(ValueType const &object) -> std::string = delete;

template<typename ValueType>
auto from_string(std::string const &stringified) -> ValueType = delete;

#endif /* SIMPLE_HTTP_DETAIL_TO_STRING_H_ */
