#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}05_do_something_by_ref"
    "DoSomethingByRef.cpp"
)


target_link_libraries("${CPL_TARGET_WEEK_PREFIX}05_do_something_by_ref"
    PRIVATE
    "cpl::boost"
)