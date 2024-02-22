
#[====[ Library ]====]
add_library("${CPL_TARGET_WEEK_PREFIX}08_speed_udl_lib" INTERFACE
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}08_speed_udl_lib" INTERFACE
    "lib"
)


#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}08_speed_udl_tests"
    "tests/SpeedTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}08_speed_udl_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}08_speed_udl_lib"
    "Catch2::Catch2WithMain"
    "cpl::boost"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}08_speed_udl_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}08_speed_udl_tests"
)


add_executable("${CPL_TARGET_WEEK_PREFIX}08_speed_udl_tests_cute"
    "tests/SpeedTestsCute.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}08_speed_udl_tests_cute" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}08_speed_udl_lib"
    "cpl::cute"
    "cpl::boost"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}08_speed_udl_tests_cute"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}08_speed_udl_tests_cute"
)
