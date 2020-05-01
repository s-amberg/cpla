#include "simple_http/response.h"

#include <type_traits>
#include <ostream>

namespace http {

  response::response(status_code code) noexcept
      : m_code{code} {

  }

  auto operator<<(std::ostream &out, response const &request) -> std::ostream &
  {
    //@formatter:off
    return out << "HTTP/1.1 " << to_string(request.m_code) << "\r\n"
               << static_cast<message<std::remove_cv_t<std::remove_reference_t<decltype(request)>>> const&>(request);
    //@formatter:on
  }

}
