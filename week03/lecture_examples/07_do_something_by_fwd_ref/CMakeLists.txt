#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}07_do_something_by_fwd_ref"
    "DoSomethingByFwdRef.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}07_do_something_by_fwd_ref"
    PRIVATE
    "cpl::boost"
)