
#include "BoundedBufferContentSuite.hpp"
#include "BoundedBufferDefaultBehaviorSuite.hpp"
#include "BoundedBufferHeapMemorySuite.hpp"
#include "BoundedBufferSemanticSuite.hpp"
#include "BoundedBufferSignaturesSuite.hpp"
#include "BoundedBufferStudentSuite.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

auto main(int argc, char const* argv[]) -> int {
  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);
  auto success = true;
  success &= runner(make_suite_bounded_buffer_signatures_suite());
  success &= runner(make_suite_bounded_buffer_default_behavior_suite());
  success &= runner(make_suite_bounded_buffer_content_suite());
  success &= runner(make_suite_bounded_buffer_heap_memory_suite());
  success &= runner(make_suite_bounded_buffer_semantic_suite());
  success &= runner(make_suite_bounded_buffer_student_suite());
  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}