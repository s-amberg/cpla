#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}sol02_sfinae_tests"
    "ConsumeTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}sol02_sfinae_tests" PRIVATE
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}sol02_sfinae_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}sol02_sfinae_tests"
)
