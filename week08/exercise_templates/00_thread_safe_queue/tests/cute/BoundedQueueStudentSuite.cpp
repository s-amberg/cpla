#include "BoundedQueueStudentSuite.hpp"

// #include "BoundedQueue.hpp"
#include <cute/cute.h>

// TODO: Add your own tests here

auto make_suite_bounded_queue_student_suite() -> cute::suite {
  return cute::suite{"BoundedQueue Student Suite", {}};
}
