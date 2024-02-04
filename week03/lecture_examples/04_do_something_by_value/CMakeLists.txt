#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}04_do_something_by_value"
    "DoSomethingByValue.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}04_do_something_by_value"
    PRIVATE
    "cpl::boost"
)