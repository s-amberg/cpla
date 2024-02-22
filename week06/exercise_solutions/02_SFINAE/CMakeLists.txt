#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}sol02_sfinae_tests"
    "ConsumeTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}sol02_sfinae_tests" PRIVATE
    "Catch2::Catch2WithMain"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}sol02_sfinae_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}sol02_sfinae_tests"
)

add_executable("${CPL_TARGET_WEEK_PREFIX}sol02_sfinae_tests_cute"
    "ConsumeTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}sol02_sfinae_tests_cute" PRIVATE
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}sol02_sfinae_tests_cute"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}sol02_sfinae_tests_cute"
)