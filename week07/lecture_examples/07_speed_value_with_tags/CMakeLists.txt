
#[====[ Library ]====]
add_library("${CPL_TARGET_WEEK_PREFIX}07_speed_value_with_tags_lib" INTERFACE
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}07_speed_value_with_tags_lib" INTERFACE
    "lib"
)


#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}07_speed_value_with_tags_tests"
    "tests/SpeedTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}07_speed_value_with_tags_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}07_speed_value_with_tags_lib"
    "Catch2::Catch2WithMain"
    "cpl::boost"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}07_speed_value_with_tags_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}07_speed_value_with_tags_tests"
)


add_executable("${CPL_TARGET_WEEK_PREFIX}07_speed_value_with_tags_tests_cute"
    "tests/SpeedTestsCute.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}07_speed_value_with_tags_tests_cute" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}07_speed_value_with_tags_lib"
    "cpl::cute"
    "cpl::boost"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}07_speed_value_with_tags_tests_cute"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}07_speed_value_with_tags_tests_cute"
)