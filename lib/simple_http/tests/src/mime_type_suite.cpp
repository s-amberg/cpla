#include "mime_type_suite.hpp"

#include "simple_http/mime_type.hpp"

#include <cute/cute.h>

TEST(to_string_returns_valid_string_representation_for_known_mime_type) {
  ASSERT_EQUAL("text/html", to_string(http::mime_type::text_html));
}

TEST(to_string_throws_for_invalid_mime_type) {
  ASSERT_THROWS(to_string(static_cast<http::mime_type>(-1)), std::invalid_argument);
}

TEST(from_string_returns_a_valid_mime_type_for_a_known_string_representation) {
  ASSERT_EQUAL(http::mime_type::image_bmp, from_string<http::mime_type>("image/bmp"));
}

TEST(from_string_throws_for_invalid_string_representation) {
  ASSERT_THROWS(from_string<http::mime_type>("NO_SUCH_MIME_TYPE"), std::invalid_argument);
}

cute::suite make_suite_mime_type_suite() {
  return cute::suite{"MIME Type Suite",
                     {
                         to_string_returns_valid_string_representation_for_known_mime_type,
                         to_string_throws_for_invalid_mime_type,
                         from_string_returns_a_valid_mime_type_for_a_known_string_representation,
                         from_string_throws_for_invalid_string_representation,
                     }};
}
