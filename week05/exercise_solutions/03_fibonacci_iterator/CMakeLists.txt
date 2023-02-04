#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}sol02_fibonacci_iterator_tests"
    "FibonacciIteratorTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}sol02_fibonacci_iterator_tests" PRIVATE
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}sol02_fibonacci_iterator_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}sol02_fibonacci_iterator_tests"
)
