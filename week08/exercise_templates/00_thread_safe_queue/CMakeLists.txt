#[====[ Library ]====]

add_library("${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_lib" INTERFACE)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_lib" INTERFACE
    "lib"
)

#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_tests"
    "tests/Test.cpp"
    "tests/bounded_queue_content_suite.cpp"
    "tests/bounded_queue_default_behavior_suite.cpp"
    "tests/bounded_queue_heap_memory_suite.cpp"
    "tests/bounded_queue_multi_threaded_suite.cpp"
    "tests/bounded_queue_non_default_constructible_element_type_suite.cpp"
    "tests/bounded_queue_semantic_suite.cpp"
    "tests/bounded_queue_signatures_suite.cpp"
    "tests/bounded_queue_single_threaded_lock_suite.cpp"
    "tests/bounded_queue_student_suite.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_lib"
    "cpl::boost"
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_tests"
)
