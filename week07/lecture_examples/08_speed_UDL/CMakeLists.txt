
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
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}08_speed_udl_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}08_speed_udl_tests"
)
