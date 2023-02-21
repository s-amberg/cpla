#[====[ Library ]====]

add_library("${CPL_TARGET_WEEK_PREFIX}ex03_dyn_array" INTERFACE)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}ex03_dyn_array" INTERFACE
    "lib"
)

#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}ex03_dyn_array_tests"
    "tests/main.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex03_dyn_array_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}ex03_dyn_array"
    "cpl::boost"
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}ex03_dyn_array_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}ex03_dyn_array_tests"
)
