#include "bounded_queue_content_suite.hpp"
#include "bounded_queue_default_behavior_suite.hpp"
#include "bounded_queue_heap_memory_suite.hpp"
#include "bounded_queue_multi_threaded_suite.hpp"
#include "bounded_queue_non_default_constructible_element_type_suite.hpp"
#include "bounded_queue_semantic_suite.hpp"
#include "bounded_queue_signatures_suite.hpp"
#include "bounded_queue_single_threaded_lock_suite.hpp"
#include "bounded_queue_student_suite.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

auto main(int argc, char const *argv[]) -> int {
  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);
  auto success = true;

  success &= runner(make_suite_bounded_queue_signatures_suite());
  success &= runner(make_suite_bounded_queue_default_behavior_suite());
  success &= runner(make_suite_bounded_queue_content_suite());
  success &= runner(make_suite_bounded_queue_semantic_suite());
  success &= runner(make_suite_bounded_queue_student_suite());
  success &= runner(make_suite_bounded_queue_heap_memory_suite());
  success &= runner(make_suite_bounded_queue_non_default_constructible_element_type_suite());
  success &= runner(make_suite_bounded_queue_single_threaded_lock_suite());
  success &= runner(make_suite_bounded_queue_multi_threaded_suite());

  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
