
#[====[ Library ]====]
add_library("${CPL_TARGET_WEEK_PREFIX}sol04_temperature_type_lib" INTERFACE
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}sol04_temperature_type_lib" INTERFACE
    "lib"
)


#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}sol04_temperature_type_tests"
"tests/TemperatureTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}sol04_temperature_type_tests" PRIVATE
"${CPL_TARGET_WEEK_PREFIX}sol04_temperature_type_lib"
"Catch2::Catch2WithMain"
"cpl::boost"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}sol04_temperature_type_tests"
COMMAND "${CPL_TARGET_WEEK_PREFIX}sol04_temperature_type_tests"
)


add_executable("${CPL_TARGET_WEEK_PREFIX}sol04_temperature_type_tests_cute"
    "tests/TemperatureTestsCute.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}sol04_temperature_type_tests_cute" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}sol04_temperature_type_lib"
    "cpl::cute"
    "cpl::boost"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}sol04_temperature_type_tests_cute"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}sol04_temperature_type_tests_cute"
)
