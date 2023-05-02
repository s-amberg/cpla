#include "simple_http/message.hpp"

#include <cstddef>
#include <string>
#include <utility>

namespace http
{

  auto message_headers::has(header field) const noexcept -> bool {
    return m_headers.count(field);
  }

  template<>
  auto message_headers::set<header::accept>(mime_type accepted) -> message_headers &
  {
    m_headers.insert({header::accept, to_string(accepted)});
    return *this;
  }

  template<>
  auto message_headers::set<header::host>(std::string host) -> message_headers &
  {
    m_headers.insert({header::host, std::move(host)});
    return *this;
  }

  template<>
  auto message_headers::set<header::host>(char const *host) -> message_headers &
  {
    return set<header::host>(static_cast<std::string>(host));
  }

  template<>
  auto message_headers::set<header::content_type>(mime_type type) -> message_headers &
  {
    m_headers.insert({header::content_type, to_string(type)});
    return *this;
  }

  template<>
  auto message_headers::set<header::content_length>(std::size_t length) -> message_headers &
  {
    if(!has(header::content_length)) {
      m_headers.insert({header::content_length, std::to_string(length)});
    } else {
      m_headers.find(header::content_length)->second = std::to_string(length);
    }
    return *this;
  }

  template<>
  auto message_headers::set<header::content_disposition>(disposition disposition) -> message_headers &
  {
    m_headers.insert({header::content_disposition, to_string(disposition)});
    return *this;
  }


}
