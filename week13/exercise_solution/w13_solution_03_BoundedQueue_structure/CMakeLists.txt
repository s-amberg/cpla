cmake_minimum_required(VERSION "3.12.0")
project("BoundedQueueTests" LANGUAGES CXX)

enable_testing()

add_executable("BoundedQueueTests"
  "test/src/bounded_queue_content_suite.cpp"
  "test/src/bounded_queue_default_behavior_suite.cpp"
  "test/src/bounded_queue_heap_memory_suite.cpp"
  "test/src/bounded_queue_multi_threaded_suite.cpp"
  "test/src/bounded_queue_non_default_constructible_element_type_suite.cpp"
  "test/src/bounded_queue_semantic_suite.cpp"
  "test/src/bounded_queue_signatures_suite.cpp"
  "test/src/bounded_queue_single_threaded_lock_suite.cpp"
  "test/src/bounded_queue_student_suite.cpp"
  "test/src/Test.cpp"
)

target_compile_features("BoundedQueueTests" PRIVATE
  "cxx_std_17"
)

target_include_directories("BoundedQueueTests" PRIVATE
  "test/third_party/cute"
  "test/include"
  "include"
)

target_link_libraries("BoundedQueueTests" PRIVATE "pthread")

add_test("Tests" "BoundedQueueTests")
