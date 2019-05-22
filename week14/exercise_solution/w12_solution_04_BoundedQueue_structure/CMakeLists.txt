cmake_minimum_required(VERSION 3.9.0)
project(BoundedQueueTests LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)
include_directories(test/include)
include_directories(test/third_party/cute)

add_executable(BoundedQueueTests
  test/src/bounded_queue_content_suite.cpp
  test/src/bounded_queue_default_behavior_suite.cpp
  test/src/bounded_queue_heap_memory_suite.cpp
  test/src/bounded_queue_multi_threaded_suite.cpp
  test/src/bounded_queue_non_default_constructible_element_type_suite.cpp
  test/src/bounded_queue_semantic_suite.cpp
  test/src/bounded_queue_signatures_suite.cpp
  test/src/bounded_queue_single_threaded_lock_suite.cpp
  test/src/bounded_queue_student_suite.cpp
  test/src/Test.cpp)

target_link_libraries(BoundedQueueTests pthread)

add_test(Tests BoundedQueueTests)
