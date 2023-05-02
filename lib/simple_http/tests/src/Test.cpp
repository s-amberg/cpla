#include "message_suite.hpp"
#include "mime_type_suite.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

auto main(int argc, char const* argv[]) -> int {
  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);
  auto success = true;
  success &= runner(make_suite_message_suite());
  success &= runner(make_suite_mime_type_suite());
  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}