#[====[ Library ]====]

add_library("${CPL_TARGET_WEEK_PREFIX}01_bounded_buffer_with_iterators_lib" INTERFACE)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}01_bounded_buffer_with_iterators_lib" INTERFACE
    "lib"
)

#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}01_bounded_buffer_with_iterators_tests"
    "tests/BoundedBufferTests.cpp"
    "tests/MemoryOperationCounter.cpp"
    "tests/BoundedBufferContentSuite.cpp"
    "tests/BoundedBufferDefaultBehaviorSuite.cpp"
    "tests/BoundedBufferHeapMemorySuite.cpp"
    "tests/BoundedBufferIteratorSuite.cpp"
    "tests/BoundedBufferNDCElementTypeSuite.cpp"
    "tests/BoundedBufferSemanticSuite.cpp"
    "tests/BoundedBufferSignaturesSuite.cpp"
    "tests/BoundedBufferStudentSuite.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}01_bounded_buffer_with_iterators_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}01_bounded_buffer_with_iterators_lib"
    "cpl::boost"
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}01_bounded_buffer_with_iterators_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}01_bounded_buffer_with_iterators_tests"
)
