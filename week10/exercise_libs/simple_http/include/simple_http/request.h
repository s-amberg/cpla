#ifndef SIMPLE_HTTP_REQUEST_H_
#define SIMPLE_HTTP_REQUEST_H_

#include "simple_http/message.h"
#include "simple_http/method.h"

#include <iosfwd>
#include <map>
#include <optional>
#include <string>
#include <type_traits>

namespace http {

  struct request : message<request> {
    explicit request(method method = http::method::get) noexcept;

    auto path(std::string path) -> request &;
    auto path() const -> std::string;

    template<typename ValueType>
    auto parameter(std::string name, ValueType value) -> request & {
      if constexpr(std::is_same_v<std::string, ValueType>) {
        m_parameters[name] = value;
      } else {
        m_parameters[name] = std::to_string(value);
      }
      return *this;
    }

    auto parameter(std::string name, std::nullopt_t) -> request &;
    auto parameter(std::string name) const -> std::optional<std::string>;
    auto has_parameter(std::string const &name) const -> bool;

    auto http_method(method method) noexcept -> request &;
    auto http_method() const noexcept -> method;

    auto friend operator<<(std::ostream & out, request const & request) -> std::ostream &;

    auto read_headers(std::istream & input) -> void;

  private:
    http::method m_method{};
    std::string m_path{};
    std::map<std::string, std::optional<std::string>> m_parameters{};
  };

}

#endif /* SIMPLE_HTTP_REQUEST_H_ */
