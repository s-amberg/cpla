#[===[ LIBRARY ]===]

add_library("${CPL_TARGET_WEEK_PREFIX}sol01_simple_tasks_lib" INTERFACE
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}sol01_simple_tasks_lib" INTERFACE "lib")



#[===[ TESTS ]===]


add_executable("${CPL_TARGET_WEEK_PREFIX}sol01_simple_tasks_tests_cute"
    "tests/SimpleTasksTestsCute.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}sol01_simple_tasks_tests_cute" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}sol01_simple_tasks_lib"
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}sol01_simple_tasks_tests_cute" COMMAND "${CPL_TARGET_WEEK_PREFIX}sol01_simple_tasks_tests_cute")


add_executable("${CPL_TARGET_WEEK_PREFIX}sol01_simple_tasks_tests"
    "tests/SimpleTasksTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}sol01_simple_tasks_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}sol01_simple_tasks_lib"
    "Catch2::Catch2WithMain"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}sol01_simple_tasks_tests" COMMAND "${CPL_TARGET_WEEK_PREFIX}sol01_simple_tasks_tests")
