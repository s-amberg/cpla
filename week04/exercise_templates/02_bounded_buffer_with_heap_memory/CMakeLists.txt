#[====[ Library ]====]

add_library("${CPL_TARGET_WEEK_PREFIX}02_bounded_buffer_with_heap_memory_lib" INTERFACE)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}02_bounded_buffer_with_heap_memory_lib" INTERFACE
    "lib"
)

#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}ex02_bounded_buffer_with_heap_memory_tests"
    "tests/catch2/MemoryOperationCounter.cpp"
    "tests/catch2/BoundedBufferContentSuite.cpp"
    "tests/catch2/BoundedBufferDefaultBehaviorSuite.cpp"
    "tests/catch2/BoundedBufferHeapMemorySuite.cpp"
    "tests/catch2/BoundedBufferSemanticSuite.cpp"
    "tests/catch2/BoundedBufferSignaturesSuite.cpp"
    "tests/catch2/BoundedBufferStudentSuite.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex02_bounded_buffer_with_heap_memory_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}02_bounded_buffer_with_heap_memory_lib"
    "cpl::boost"
    "Catch2::Catch2WithMain"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}ex02_bounded_buffer_with_heap_memory_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}ex02_bounded_buffer_with_heap_memory_tests"
)


add_executable("${CPL_TARGET_WEEK_PREFIX}ex02_bounded_buffer_with_heap_memory_cute_tests"
    "tests/cute/BoundedBufferTests.cpp"
    "tests/cute/MemoryOperationCounter.cpp"
    "tests/cute/BoundedBufferContentSuite.cpp"
    "tests/cute/BoundedBufferDefaultBehaviorSuite.cpp"
    "tests/cute/BoundedBufferHeapMemorySuite.cpp"
    "tests/cute/BoundedBufferSemanticSuite.cpp"
    "tests/cute/BoundedBufferSignaturesSuite.cpp"
    "tests/cute/BoundedBufferStudentSuite.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex02_bounded_buffer_with_heap_memory_cute_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}02_bounded_buffer_with_heap_memory_lib"
    "cpl::boost"
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}ex02_bounded_buffer_with_heap_memory_cute_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}ex02_bounded_buffer_with_heap_memory_cute_tests"
)
