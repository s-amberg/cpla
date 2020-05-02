#ifndef INCLUDE_SIMPLE_HTTP_MESSAGE_H_
#define INCLUDE_SIMPLE_HTTP_MESSAGE_H_

#include "simple_http/header.h"
#include "simple_http/mime_type.h"
#include "simple_http/disposition.h"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <istream>
#include <iterator>
#include <map>
#include <ostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace http {

  struct message_headers {
    template<header HeaderField, typename ... ValueTypes>
    auto set(ValueTypes ... value) -> message_headers & = delete;

    template<header HeaderField>
    auto get() const -> std::string {
      auto value = m_headers.find(HeaderField);
      if (value == cend(m_headers)) {
        throw std::runtime_error{"Header '" + to_string(HeaderField) + "' not found!"};
      }
      return value->second;
    }

    auto has(header field) const noexcept -> bool;

  protected:
    std::multimap<http::header, std::string> m_headers{};
  };

  template<>
  auto message_headers::set<header::accept>(mime_type accepted) -> message_headers &;

  template<>
  auto message_headers::set<header::host>(std::string host) -> message_headers &;

  template<>
  auto message_headers::set<header::host>(char const *host) -> message_headers &;

  template<>
  auto message_headers::set<header::content_type>(mime_type type) -> message_headers &;

  template<>
  auto message_headers::set<header::content_length>(std::size_t length) -> message_headers &;

  template<>
  auto message_headers::set<header::content_disposition>(disposition disposition) -> message_headers &;

  template<typename DerivedType>
  struct message : message_headers {
    template<header HeaderField, typename ...ValueTypes>
    [[nodiscard]] auto set(ValueTypes &&... value) -> DerivedType &
    {
      return static_cast<DerivedType&>(message_headers::template set<HeaderField>(std::forward<ValueTypes>(value)...));
    }

    template<header HeaderField>
    auto get() const {
      auto value = message_headers::template get<HeaderField>();

      if constexpr (HeaderField == header::content_length) {
        return std::stoull(message_headers::template get<HeaderField>());
      } else if constexpr (HeaderField == header::content_disposition) {
        return from_string<disposition>(value);
      } else {
        return value;
      }
    }

    auto body(std::string &&body) noexcept(std::is_nothrow_move_assignable_v<std::string>) -> DerivedType &
    {
      m_body = std::move(body);
      (void) set<http::header::content_length>(body.size());
      return static_cast<DerivedType&>(*this);
    }

    auto body(std::string const &body) -> DerivedType &
    {
      m_body = body;
      (void) set<http::header::content_length>(body.size());
      return static_cast<DerivedType&>(*this);
    }

    auto body(std::vector<std::byte> const &body) -> DerivedType &
    {
      m_body.resize(body.size());
      (void) set<http::header::content_length>(body.size());
      transform(cbegin(body), cend(body), begin(m_body), [](auto part) {
        return static_cast<char>(part);
      });
      return static_cast<DerivedType&>(*this);
    }

    auto body(std::istream &input) -> DerivedType &
    {
      m_body.clear();
      copy(std::istreambuf_iterator<char>{input}, std::istreambuf_iterator<char>{}, back_inserter(m_body));
      return static_cast<DerivedType&>(*this);
    }

    auto body() const -> std::string
    {
      return m_body;
    }

    auto complete() const -> bool {
      return !has(header::content_length) || get<header::content_length>() == m_body.size();
    }

    template<typename Derived>
    friend auto operator<<(std::ostream &out, message<Derived> const &message) -> std::ostream &;

  protected:
    auto read_headers(std::istream &input) -> void {
      auto line = std::string{};
      while (getline(input, line)) {
        line.erase(begin(line), find_if(begin(line), end(line), [](auto chr) {
          return !std::isspace(chr);
        }));
        line.erase(find_if(rbegin(line), rend(line), [](auto chr) {
          return !std::isspace(chr);
        }).base(),
                   end(line));
        if (line.empty()) {
          return;
        }

        auto split_position = line.find(":");
        if (split_position == line.npos) {
          throw std::invalid_argument{"invalid header format"};
        }

        try {
          auto header = from_string<http::header>(line.substr(0, split_position));

          auto value_start = line.find_first_not_of(' ', split_position + 1);
          if (value_start == line.npos) {
            throw std::invalid_argument{"missing header value"};
          }
          auto value = line.substr(value_start);

          m_headers.insert({header, value});
        } catch (unknown_header const&) {
        }
      }
    }

  private:
    std::string m_body{};
  };

  template<typename DerivedType>
  auto operator<<(std::ostream &out, message<DerivedType> const &message) -> std::ostream &
  {
    auto output_iterator = std::ostream_iterator<std::string>{out, "\r\n"};
    transform(cbegin(message.m_headers), cend(message.m_headers), output_iterator, [](auto const &entry) {
      return to_string(entry.first) + ": " + entry.second;
    });
    return out << "\r\n" << message.body();
  }

}

#endif /* INCLUDE_SIMPLE_HTTP_MESSAGE_H_ */
