#[===[ LIBRARY ]===]

add_library("${CPL_TARGET_WEEK_PREFIX}ex01_simple_tasks_lib" INTERFACE
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}ex01_simple_tasks_lib" INTERFACE "lib")



#[===[ TESTS ]===]


add_executable("${CPL_TARGET_WEEK_PREFIX}ex01_simple_tasks_tests"
    "tests/SimpleTasksTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex01_simple_tasks_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}ex01_simple_tasks_lib"
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}ex01_simple_tasks_tests" COMMAND "${CPL_TARGET_WEEK_PREFIX}ex01_simple_tasks_tests")
