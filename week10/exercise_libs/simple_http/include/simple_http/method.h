#ifndef SIMPLE_HTTP_METHOD_H_
#define SIMPLE_HTTP_METHOD_H_

#include "simple_http/detail/to_string.h"

#include <string>

namespace http {

  enum struct method {
    get,
    put,
    post,
    delete_,
    update,
  };

}

template<>
auto to_string(http::method const &object) -> std::string;

template<>
auto from_string(std::string const &stringified) -> http::method;

#endif /* SIMPLE_HTTP_METHOD_H_ */
