#[====[ Library ]====]

add_library("${CPL_TARGET_WEEK_PREFIX}ex03_bounded_buffer_for_non_default_constructible_types_lib" INTERFACE)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}ex03_bounded_buffer_for_non_default_constructible_types_lib" INTERFACE
    "lib"
)

#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}ex03_bounded_buffer_for_non_default_constructible_types_tests"
    "tests/catch2/MemoryOperationCounter.cpp"
    "tests/catch2/BoundedBufferContentSuite.cpp"
    "tests/catch2/BoundedBufferDefaultBehaviorSuite.cpp"
    "tests/catch2/BoundedBufferHeapMemorySuite.cpp"
    "tests/catch2/BoundedBufferNDCElementTypeSuite.cpp"
    "tests/catch2/BoundedBufferSemanticSuite.cpp"
    "tests/catch2/BoundedBufferSignaturesSuite.cpp"
    "tests/catch2/BoundedBufferStudentSuite.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex03_bounded_buffer_for_non_default_constructible_types_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}ex03_bounded_buffer_for_non_default_constructible_types_lib"
    "cpl::boost"
    "Catch2::Catch2WithMain"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}ex03_bounded_buffer_for_non_default_constructible_types_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}ex03_bounded_buffer_for_non_default_constructible_types_tests"
)


# add_executable("${CPL_TARGET_WEEK_PREFIX}ex03_bounded_buffer_for_non_default_constructible_types_cute_tests"
#     "tests/cute/BoundedBufferTests.cpp"
#     "tests/cute/MemoryOperationCounter.cpp"
#     "tests/cute/BoundedBufferContentSuite.cpp"
#     "tests/cute/BoundedBufferDefaultBehaviorSuite.cpp"
#     "tests/cute/BoundedBufferHeapMemorySuite.cpp"
#     "tests/cute/BoundedBufferNDCElementTypeSuite.cpp"
#     "tests/cute/BoundedBufferSemanticSuite.cpp"
#     "tests/cute/BoundedBufferSignaturesSuite.cpp"
#     "tests/cute/BoundedBufferStudentSuite.cpp"
# )

# target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex03_bounded_buffer_for_non_default_constructible_types_cute_tests" PRIVATE
#     "${CPL_TARGET_WEEK_PREFIX}ex03_bounded_buffer_for_non_default_constructible_types_lib"
#     "cpl::boost"
#     "cpl::cute"
# )

# add_test(NAME "${CPL_TARGET_WEEK_PREFIX}ex03_bounded_buffer_for_non_default_constructible_types_cute_tests"
#     COMMAND "${CPL_TARGET_WEEK_PREFIX}ex03_bounded_buffer_for_non_default_constructible_types_cute_tests"
# )