cmake_minimum_required(VERSION "3.12.0")
project("BoundedQueueTests" LANGUAGES CXX)

add_executable("BoundedQueueTests"
  "bounded_queue_content_suite.cpp"
  "bounded_queue_default_behavior_suite.cpp"
  "bounded_queue_heap_memory_suite.cpp"
  "bounded_queue_multi_threaded_suite.cpp"
  "bounded_queue_non_default_constructible_element_type_suite.cpp"
  "bounded_queue_semantic_suite.cpp"
  "bounded_queue_signatures_suite.cpp"
  "bounded_queue_single_threaded_lock_suite.cpp"
  "bounded_queue_student_suite.cpp"
  "Test.cpp"
)

target_compile_features("BoundedQueueTests" PRIVATE
  "cxx_std_17"
)

target_include_directories("BoundedQueueTests" PRIVATE
  "cute"
)

target_link_libraries("BoundedQueueTests" PRIVATE "pthread")
