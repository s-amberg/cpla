#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}ex01_not_on_heap_tests"
    "NotOnHeapTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex01_not_on_heap_tests" PRIVATE
    "Catch2::Catch2WithMain"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}ex01_not_on_heap_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}ex01_not_on_heap_tests"
)


# add_executable("${CPL_TARGET_WEEK_PREFIX}ex01_not_on_heap_cute_tests"
#     "NotOnHeapCuteTests.cpp"
# )

# target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex01_not_on_heap_cute_tests" PRIVATE
#     "cpl::cute"
# )

# add_test(NAME "${CPL_TARGET_WEEK_PREFIX}ex01_not_on_heap_cute_tests"
#     COMMAND "${CPL_TARGET_WEEK_PREFIX}ex01_not_on_heap_cute_tests"
# )
