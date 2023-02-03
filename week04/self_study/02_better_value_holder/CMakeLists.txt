#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}02_better_value_holder_tests"
    "BetterValueHolderTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}02_better_value_holder_tests" PRIVATE
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}02_better_value_holder_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}02_better_value_holder_tests"
)
