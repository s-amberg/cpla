#[===[ LIBRARY ]===]

add_library("${CPL_TARGET_WEEK_PREFIX}sol02_fraction_lib" INTERFACE
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}sol02_fraction_lib" INTERFACE "lib")



#[===[ TESTS ]===]


add_executable("${CPL_TARGET_WEEK_PREFIX}sol02_fraction_tests_cute"
"tests/FractionTestsCute.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}sol02_fraction_tests_cute" PRIVATE
"${CPL_TARGET_WEEK_PREFIX}sol02_fraction_lib"
"cpl::boost"
"cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}sol02_fraction_tests_cute" COMMAND "${CPL_TARGET_WEEK_PREFIX}sol02_fraction_tests_cute")


add_executable("${CPL_TARGET_WEEK_PREFIX}sol02_fraction_tests"
    "tests/FractionTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}sol02_fraction_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}sol02_fraction_lib"
    "cpl::boost"
    "Catch2::Catch2WithMain"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}sol02_fraction_tests" COMMAND "${CPL_TARGET_WEEK_PREFIX}sol02_fraction_tests")
