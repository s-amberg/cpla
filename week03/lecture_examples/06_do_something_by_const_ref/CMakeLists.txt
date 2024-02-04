#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}06_do_something_by_const_ref"
    "DoSomethingByConstRef.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}06_do_something_by_const_ref"
    PRIVATE
    "cpl::boost"
)