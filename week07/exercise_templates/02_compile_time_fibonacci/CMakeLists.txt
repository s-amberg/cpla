
#[====[ Library ]====]
add_library("${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_lib" INTERFACE
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_lib" INTERFACE
    "lib"
)


#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_tests"
"tests/FibonacciTests.cpp"
)

# #for gcc
# target_compile_options("${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_tests" PRIVATE "-fconstexpr-ops-limit=100000000000000")
# target_compile_options("${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_tests" PRIVATE "-fconstexpr-cache-depth=50")

# #for clang
# target_compile_options("${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_tests" PRIVATE "-fconstexpr-steps=4000000000")

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_tests" PRIVATE
"${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_lib"
"Catch2::Catch2WithMain"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_tests"
COMMAND "${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_tests"
)

add_executable("${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_benchmark"
    "tests/FibonacciBenchmark.cpp"
)

target_compile_options("${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_benchmark" PRIVATE "-O3")

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_benchmark" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_lib"
    "Catch2::Catch2WithMain"
)


add_executable("${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_tests_cute"
    "tests/FibonacciTestsCute.cpp"
)

# #for gcc
# target_compile_options("${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_tests" PRIVATE "-fconstexpr-ops-limit=100000000000000")
# target_compile_options("${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_tests" PRIVATE "-fconstexpr-cache-depth=50")

# #for clang
# target_compile_options("${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_tests" PRIVATE "-fconstexpr-steps=4000000000")

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_tests_cute" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_lib"
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_tests_cute"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}ex02_compile_time_fibonacci_tests_cute"
)
