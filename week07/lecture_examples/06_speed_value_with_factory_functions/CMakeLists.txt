
#[====[ Library ]====]
add_library("${CPL_TARGET_WEEK_PREFIX}06_speed_value_with_factory_functions_lib"
    "lib/Speed.cpp"
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}06_speed_value_with_factory_functions_lib" PUBLIC
    "lib"
)


#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}06_speed_value_with_factory_functions_tests"
    "tests/SpeedTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}06_speed_value_with_factory_functions_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}06_speed_value_with_factory_functions_lib"
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}06_speed_value_with_factory_functions_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}06_speed_value_with_factory_functions_tests"
)
