#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}07_new_delete_overload_tests"
    "NotOnHeapTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}07_new_delete_overload_tests" PRIVATE
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}07_new_delete_overload_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}07_new_delete_overload_tests"
)
