
#[====[ Library ]====]
add_library("${CPL_TARGET_WEEK_PREFIX}sol02_compile_time_fibonacci_lib" INTERFACE
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}sol02_compile_time_fibonacci_lib" INTERFACE
    "lib"
)


#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}sol02_compile_time_fibonacci_tests"
    "tests/FibonacciTests.cpp"
)

target_compile_options("${CPL_TARGET_WEEK_PREFIX}sol02_compile_time_fibonacci_tests" PRIVATE "-O3")

# #for gcc
# target_compile_options("${CPL_TARGET_WEEK_PREFIX}sol02_compile_time_fibonacci_tests" PRIVATE "-fconstexpr-ops-limit=100000000000000")
# target_compile_options("${CPL_TARGET_WEEK_PREFIX}sol02_compile_time_fibonacci_tests" PRIVATE "-fconstexpr-cache-depth=50")

# #for clang
# target_compile_options("${CPL_TARGET_WEEK_PREFIX}sol02_compile_time_fibonacci_tests" PRIVATE "-fconstexpr-steps=4000000000")

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}sol02_compile_time_fibonacci_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}sol02_compile_time_fibonacci_lib"
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}sol02_compile_time_fibonacci_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}sol02_compile_time_fibonacci_tests"
)
