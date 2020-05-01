#include "mime_type_suite.h"

#include "simple_http/mime_type.h"

#include "cute.h"

void to_string_returns_valid_string_representation_for_known_mime_type() {
	ASSERT_EQUAL("text/html", to_string(http::mime_type::text_html));
}

void to_string_throws_for_invalid_mime_type() {
	ASSERT_THROWS(to_string(static_cast<http::mime_type>(-1)), std::invalid_argument);
}

void from_string_returns_a_valid_mime_type_for_a_known_string_representation() {
	ASSERT_EQUAL(http::mime_type::image_bmp, from_string<http::mime_type>("image/bmp"));
}

void from_string_throws_for_invalid_string_representation() {
	ASSERT_THROWS(from_string<http::mime_type>("NO_SUCH_MIME_TYPE"), std::invalid_argument);
}

cute::suite make_suite_mime_type_suite() {
	cute::suite s { };
	s.push_back(CUTE(to_string_returns_valid_string_representation_for_known_mime_type));
	s.push_back(CUTE(to_string_throws_for_invalid_mime_type));
	s.push_back(CUTE(from_string_returns_a_valid_mime_type_for_a_known_string_representation));
	s.push_back(CUTE(from_string_throws_for_invalid_string_representation));
	return s;
}
