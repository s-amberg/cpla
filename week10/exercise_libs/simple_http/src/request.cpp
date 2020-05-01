#include "simple_http/request.h"

#include "simple_http/method.h"

#include <algorithm>
#include <cctype>
#include <iterator>
#include <map>
#include <optional>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

auto extract_path(std::string const &path) -> std::string {
  auto split = path.find('?');
  return path.substr(0, split);
}

auto extract_parameters(std::string const &path) -> std::map<std::string, std::optional<std::string>> {
  auto split = path.find('?');
  if (split == path.npos) {
    return {};
  }

  auto query_elements = std::vector<std::string>{};
  while (split != path.npos) {
    auto element_split = path.find('&', split + 1);
    query_elements.push_back(path.substr(split + 1, element_split - split - 1));
    split = element_split;
  }

  auto parameters = std::map<std::string, std::optional<std::string>>{};
  transform(cbegin(query_elements), cend(query_elements), std::inserter(parameters, end(parameters)), [](auto element) {
    auto name_split = element.find('=');
    auto name = element.substr(0, name_split);
    auto value = name_split != element.npos ? std::optional{element.substr(name_split + 1)} : std::nullopt;
    return std::pair{name, value};
  });

  return parameters;
}

namespace http {

  request::request(method method) noexcept
      : m_method{method} {
  }

  auto request::path(std::string path) -> request &
  {
    m_path = std::move(path);
    return *this;
  }

  auto request::path() const -> std::string
  {
    return m_path;
  }

  auto request::parameter(std::string name, std::nullopt_t) -> request & {
    m_parameters[name] = std::nullopt;
    return *this;
  }

  auto request::parameter(std::string name) const -> std::optional<std::string> {
    if (m_parameters.count(name)) {
      return m_parameters.at(name);
    } else {
      return {};
    }
  }

  auto request::has_parameter(std::string const &name) const -> bool {
    return m_parameters.count(name);
  }

  auto request::http_method(method method) noexcept -> request & {
    m_method = method;
    return *this;
  }

  auto request::http_method() const noexcept -> method
  {
    return m_method;
  }

  auto request::read_headers(std::istream &input) -> void {
    auto line = std::string{};

    while (std::isspace(input.peek())) {
      input.ignore();
    }

    if (!getline(input, line)) {
      throw std::invalid_argument{"missing method"};
    }

    std::string method{}, path{}, version{};
    auto method_stream = std::istringstream{line};

    if (!(method_stream >> method >> path >> version) || version != "HTTP/1.1") {
      throw std::invalid_argument{"failed to parse method line"};
    }

    m_method = from_string<http::method>(method);
    m_path = extract_path(path);
    m_parameters = extract_parameters(path);

    message<request>::read_headers(input);
  }

  auto operator<<(std::ostream &out, request const &request) -> std::ostream &
  {
    out << to_string(request.m_method) << ' ' << (request.m_path.empty() ? "/" : request.m_path);

    if (!request.m_parameters.empty()) {
      auto first = true;
      transform(cbegin(request.m_parameters), cend(request.m_parameters), std::ostream_iterator<std::string>{out, ""}, [&](auto entry) {
        auto buffer = std::ostringstream{};
        (buffer << (first ? '?' : '&') << entry.first << (entry.second ? "=" : "") << entry.second.value_or("")), first = false;
        return buffer.str();
      });
    }
    return out << " HTTP/1.1\r\n" << static_cast<message<std::remove_cv_t<std::remove_reference_t<decltype(request)>>> const&>(request);
  }
}

