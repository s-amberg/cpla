#ifndef SIMPLE_HTTP_RESPONSE_H_
#define SIMPLE_HTTP_RESPONSE_H_

#include "simple_http/message.h"
#include "simple_http/status_code.h"

#include <iosfwd>

namespace http {

  struct response : message<response> {
    explicit response(status_code code) noexcept;
    explicit response(std::istream & stream);

    auto status() const noexcept -> status_code;

    auto friend operator<<(std::ostream & out, response const & request) -> std::ostream &;

  private:
    status_code m_code;
  };

}

#endif /* SIMPLE_HTTP_RESPONSE_H_ */
