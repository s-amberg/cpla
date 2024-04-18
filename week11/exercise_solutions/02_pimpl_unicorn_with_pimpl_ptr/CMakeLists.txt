
#[====[ Library ]====]
add_library("${CPL_TARGET_WEEK_PREFIX}sol02_pimpl_unicorn_with_pimpl_ptr_lib"
    "lib/Unicorn.cpp"
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}sol02_pimpl_unicorn_with_pimpl_ptr_lib" PUBLIC
    "lib"
)

#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}sol02_pimpl_unicorn_with_pimpl_ptr_tests"
    "tests/CreateFreddy.cpp"
    "tests/Tests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}sol02_pimpl_unicorn_with_pimpl_ptr_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}sol02_pimpl_unicorn_with_pimpl_ptr_lib"
    "Catch2::Catch2WithMain"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}sol02_pimpl_unicorn_with_pimpl_ptr_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}sol02_pimpl_unicorn_with_pimpl_ptr_tests"
)


add_executable("${CPL_TARGET_WEEK_PREFIX}sol02_pimpl_unicorn_with_pimpl_ptr_tests_cute"
    "tests/CreateFreddy.cpp"
    "tests/TestsCute.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}sol02_pimpl_unicorn_with_pimpl_ptr_tests_cute" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}sol02_pimpl_unicorn_with_pimpl_ptr_lib"
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}sol02_pimpl_unicorn_with_pimpl_ptr_tests_cute"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}sol02_pimpl_unicorn_with_pimpl_ptr_tests_cute"
)