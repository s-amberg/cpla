#include "NotOnHeap.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>



// Allocation as local variable
TEST(test_stack_allocation_works) {
}


auto main(int argc, char const* argv[]) -> int {
  auto suite = cute::suite{"NotOnHeap Tests",
                           {
                               test_stack_allocation_works,
                           }};

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}
