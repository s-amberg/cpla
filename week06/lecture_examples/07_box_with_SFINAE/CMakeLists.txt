#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}07_box_with_sfinae_tests"
    "BoxWithSFINAETests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}07_box_with_sfinae_tests" PRIVATE
    "Catch2::Catch2WithMain"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}07_box_with_sfinae_tests"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}07_box_with_sfinae_tests"
)
