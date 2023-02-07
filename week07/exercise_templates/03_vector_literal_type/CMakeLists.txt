
#[====[ Library ]====]
add_library("${CPL_TARGET_WEEK_PREFIX}ex03_vector_literal_type_lib" INTERFACE
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}ex03_vector_literal_type_lib" INTERFACE
    "lib"
)


#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}ex03_vector_literal_type_tests"
    "tests/VectorTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex03_vector_literal_type_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}ex03_vector_literal_type_lib"
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}ex03_vector_literal_type_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}ex03_vector_literal_type_tests"
)
