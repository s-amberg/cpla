#[====[ Library ]====]

add_library("${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_lib" INTERFACE)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_lib" INTERFACE
    "lib"
)

#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_tests"
  "tests/catch2/BoundedQueueContentSuite.cpp"
  "tests/catch2/BoundedQueueDefaultBehaviorSuite.cpp"
  "tests/catch2/BoundedQueueHeapMemorySuite.cpp"
  "tests/catch2/BoundedQueueMultiThreadedSuite.cpp"
  "tests/catch2/BoundedQueueNonDefaultConstructibleElementTypeSuite.cpp"
  "tests/catch2/BoundedQueueSemanticSuite.cpp"
  "tests/catch2/BoundedQueueSignaturesSuite.cpp"
  "tests/catch2/BoundedQueueSingleThreadedLockSuite.cpp"
  "tests/catch2/BoundedQueueStudentSuite.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_tests" PRIVATE
  "${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_lib"
  "cpl::boost"
  "Catch2::Catch2WithMain"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_tests"
  COMMAND "${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_tests"
)

add_executable("${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_tests_cute"
    "tests/cute/Test.cpp"
    "tests/cute/BoundedQueueContentSuite.cpp"
    "tests/cute/BoundedQueueDefaultBehaviorSuite.cpp"
    "tests/cute/BoundedQueueHeapMemorySuite.cpp"
    "tests/cute/BoundedQueueMultiThreadedSuite.cpp"
    "tests/cute/BoundedQueueNonDefaultConstructibleElementTypeSuite.cpp"
    "tests/cute/BoundedQueueSemanticSuite.cpp"
    "tests/cute/BoundedQueueSignaturesSuite.cpp"
    "tests/cute/BoundedQueueSingleThreadedLockSuite.cpp"
    "tests/cute/BoundedQueueStudentSuite.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_tests_cute" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_lib"
    "cpl::boost"
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_tests_cute"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}00_thread_safe_queue_tests_cute"
)
