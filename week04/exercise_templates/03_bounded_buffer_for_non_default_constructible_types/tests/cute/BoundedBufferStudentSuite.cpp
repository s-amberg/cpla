#include "BoundedBufferStudentSuite.hpp"

#include <cute/cute.h>

// TODO: Add your own tests here

TEST(testEmpty) {}

auto make_suite_bounded_buffer_student_suite() -> cute::suite {
  return cute::suite{"BoundedBuffer Student Suite",
                     {
                         testEmpty,
                     }};
}
