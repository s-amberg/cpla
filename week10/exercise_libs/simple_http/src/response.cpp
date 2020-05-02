#include "simple_http/response.h"

#include <cctype>
#include <cstddef>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace http {

  response::response(status_code code) noexcept
      : m_code{code} {
        (void)set<header::content_length>(static_cast<std::size_t>(0));
  }

  response::response(std::istream &input) : m_code{static_cast<status_code>(-1)} {
    auto line = std::string{};

    while (std::isspace(input.peek())) {
      input.ignore();
    }

    if (!getline(input, line)) {
      throw std::invalid_argument{"missing http version"};
    }

    std::string version{}, code{}, code_message{};
    auto method_stream = std::istringstream{line};

    if (!(method_stream >> version >> code >> code_message) || version != "HTTP/1.1") {
      throw std::invalid_argument{"failed to parse method line"};
    }

    m_code = to_status_code(std::stoi(code));
    read_headers(input);
  }

  auto operator<<(std::ostream &out, response const &request) -> std::ostream &
  {
    //@formatter:off
    return out << "HTTP/1.1 " << to_string(request.m_code) << "\r\n"
               << static_cast<message<std::remove_cv_t<std::remove_reference_t<decltype(request)>>> const&>(request);
    //@formatter:on
}  }
