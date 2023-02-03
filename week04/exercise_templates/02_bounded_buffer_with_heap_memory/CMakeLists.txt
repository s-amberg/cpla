#[====[ Library ]====]

add_library("${CPL_TARGET_WEEK_PREFIX}02_bounded_buffer_with_heap_memory_lib" INTERFACE)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}02_bounded_buffer_with_heap_memory_lib" INTERFACE
    "lib"
)

#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}02_bounded_buffer_with_heap_memory_tests"
    "tests/BoundedBufferTests.cpp"
    "tests/MemoryOperationCounter.cpp"
    "tests/BoundedBufferContentSuite.cpp"
    "tests/BoundedBufferDefaultBehaviorSuite.cpp"
    "tests/BoundedBufferHeapMemorySuite.cpp"
    "tests/BoundedBufferSemanticSuite.cpp"
    "tests/BoundedBufferSignaturesSuite.cpp"
    "tests/BoundedBufferStudentSuite.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}02_bounded_buffer_with_heap_memory_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}02_bounded_buffer_with_heap_memory_lib"
    "cpl::boost"
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}02_bounded_buffer_with_heap_memory_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}02_bounded_buffer_with_heap_memory_tests"
)
