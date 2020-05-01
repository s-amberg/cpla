#ifndef SIMPLE_HTTP_DISPOSITION_H_
#define SIMPLE_HTTP_DISPOSITION_H_

#include "simple_http/detail/to_string.h"

#include <string>

namespace http {

  enum struct disposition {
    attachment,
    inline_,
  };

}

template<>
auto to_string(http::disposition const &object) -> std::string;

template<>
auto from_string(std::string const &stringified) -> http::disposition;

#endif /* SIMPLE_HTTP_METHOD_H_ */
