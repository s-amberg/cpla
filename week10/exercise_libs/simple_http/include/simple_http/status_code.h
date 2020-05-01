#ifndef SIMPLE_HTTP_STATUS_CODE_H_
#define SIMPLE_HTTP_STATUS_CODE_H_

#include "simple_http/detail/to_string.h"

#include <string>

namespace http {

  enum struct status_code {
    // 1xx
    continue_ = 100,
    switching_protocols,
    processing,
    early_hints,

    // 2xx
    ok = 200,
    created,
    accepted,
    non_authoritative_information,
    no_content,
    reset_content,
    partial_content,
    multi_status,
    already_reported,
    im_used = 226,

    // 3xx
    multiple_choices = 300,
    moved_permanently,
    found,
    see_other,
    not_modified,
    use_proxy,
    switch_proxy,
    temporary_redirect,
    permanent_redirect,

    // 4xx
    bad_request = 400,
    unauthorized,
    payment_required,
    forbidden,
    not_found,
    method_not_allowed,
    not_acceptable,
    proxy_authentication_required,
    request_timeout,
    conflict,
    gone,
    length_required,
    precondition_failed,
    payload_too_large,
    uri_too_long,
    unsupported_media_type,
    range_not_satisfiable,
    i_am_a_teapot,
    misdirected_request = 421,
    unprocessable_entity,
    locked,
    failed_dependency,
    too_early,
    upgrade_required,
    precondition_required = 428,
    too_many_requests,
    request_header_fields_too_large = 431,
    unavailable_for_legal_reasons = 451,

    // 5xx
    internal_server_error = 500,
    not_implemented,
    bad_gateway,
    service_unavailable,
    gateway_timeout,
    http_version_not_supported,
    variant_also_negotiates,
    insufficient_storage,
    loop_detected,
    not_extended = 510,
    network_authentication_required
  };

}

template<>
auto to_string(http::status_code const &object) -> std::string;

template<>
auto from_string(std::string const &stringified) -> http::status_code;

#endif /* SIMPLE_HTTP_STATUS_CODE_H_ */
