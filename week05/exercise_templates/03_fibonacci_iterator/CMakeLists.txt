#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}ex02_fibonacci_iterator_tests"
    "FibonacciIteratorTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex02_fibonacci_iterator_tests" PRIVATE
    "Catch2::Catch2WithMain"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}ex02_fibonacci_iterator_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}ex02_fibonacci_iterator_tests"
)

add_executable("${CPL_TARGET_WEEK_PREFIX}ex02_fibonacci_iterator_cute_tests"
    "FibonacciIteratorCuteTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex02_fibonacci_iterator_cute_tests" PRIVATE
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}ex02_fibonacci_iterator_cute_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}ex02_fibonacci_iterator_cute_tests"
)
