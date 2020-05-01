#include "simple_http/status_code.h"

#include <array>
#include <stdexcept>
#include <string>
#include <utility>

using namespace http;

// @formatter:off
auto constexpr string_map = std::array{
  std::pair{status_code::continue_, "Continue"},
  std::pair{status_code::switching_protocols, "Switching Protocols"},
  std::pair{status_code::processing, "Processing"},
  std::pair{status_code::early_hints, "Early Hints"},
  std::pair{status_code::ok, "OK"},
  std::pair{status_code::created, "Created"},
  std::pair{status_code::accepted, "Accepted"},
  std::pair{status_code::non_authoritative_information, "Non-Authoritative Information"},
  std::pair{status_code::no_content, "No Content"},
  std::pair{status_code::reset_content, "Reset Content"},
  std::pair{status_code::partial_content, "Partial Content"},
  std::pair{status_code::multi_status, "Multi-Status"},
  std::pair{status_code::already_reported, "Already Reported"},
  std::pair{status_code::im_used, "IM Used"},
  std::pair{status_code::multiple_choices, "Multiple Choices"},
  std::pair{status_code::moved_permanently, "Move Permanently"},
  std::pair{status_code::found, "Found"},
  std::pair{status_code::see_other, "See Other"},
  std::pair{status_code::not_modified, "Not Modified"},
  std::pair{status_code::use_proxy, "Use Proxy"},
  std::pair{status_code::switch_proxy, "Switch Proxy"},
  std::pair{status_code::temporary_redirect, "Temporary Redirect"},
  std::pair{status_code::permanent_redirect, "Permanent Redirect"},
  std::pair{status_code::bad_request, "Bad Request"},
  std::pair{status_code::unauthorized, "Unauthorized"},
  std::pair{status_code::payment_required, "Payment Required"},
  std::pair{status_code::forbidden, "Forbidden"},
  std::pair{status_code::not_found, "Not Found"},
  std::pair{status_code::method_not_allowed, "Method Not Allowed"},
  std::pair{status_code::not_acceptable, "Not Acceptable"},
  std::pair{status_code::proxy_authentication_required, "Proxy Authentication Required"},
  std::pair{status_code::request_timeout, "Request Timeout"},
  std::pair{status_code::conflict, "Conflict"},
  std::pair{status_code::gone, "Gone"},
  std::pair{status_code::length_required, "Length Required"},
  std::pair{status_code::precondition_failed, "Precondition Failed"},
  std::pair{status_code::payload_too_large, "Payload Too Large"},
  std::pair{status_code::uri_too_long, "URI Too Long"},
  std::pair{status_code::unsupported_media_type, "Unsupported Media Type"},
  std::pair{status_code::range_not_satisfiable, "Range Not Satisfiable"},
  std::pair{status_code::i_am_a_teapot, "I'm a teapot"},
  std::pair{status_code::misdirected_request, "Misdirected Request"},
  std::pair{status_code::unprocessable_entity, "Unprocessable Entity"},
  std::pair{status_code::locked, "Locked"},
  std::pair{status_code::failed_dependency, "Failed Dependency"},
  std::pair{status_code::too_early, "Too Early"},
  std::pair{status_code::upgrade_required, "Upgrade Required"},
  std::pair{status_code::precondition_required, "Precondition Required"},
  std::pair{status_code::too_many_requests, "Too Many Requests"},
  std::pair{status_code::request_header_fields_too_large, "Request Header Fields Too Large"},
  std::pair{status_code::unavailable_for_legal_reasons, "Unavailable For Legal Reasons"},
  std::pair{status_code::internal_server_error, "Internal Server Error"},
  std::pair{status_code::not_implemented, "Not Implemented"},
  std::pair{status_code::bad_gateway, "Bad Gateway"},
  std::pair{status_code::service_unavailable, "Service Unavailable"},
  std::pair{status_code::gateway_timeout, "Gateway Timeout"},
  std::pair{status_code::http_version_not_supported, "HTTP Version Not Supported"},
  std::pair{status_code::variant_also_negotiates, "Variant Also Negotiates"},
  std::pair{status_code::insufficient_storage, "Insufficient Storage"},
  std::pair{status_code::loop_detected, "Loop Detected"},
  std::pair{status_code::not_extended, "Not Extended"},
  std::pair{status_code::network_authentication_required, "Network Authentication Required"},
};
// @formatter:on
template<>
auto to_string(status_code const &object) -> std::string {
  auto found = detail::to_string_impl(string_map, object);
  if (found) {
    return std::to_string(static_cast<int>(object)) + " " + *found;
  }

  throw std::invalid_argument{"invalid mime type: " + std::to_string(static_cast<int>(object))};
}

template<>
auto from_string(std::string const &stringified) -> status_code {
  auto found = detail::from_string_impl(string_map, stringified);
  if (found) {
    return *found;
  }

  throw std::invalid_argument{"invalid mime type: " + stringified};
}
