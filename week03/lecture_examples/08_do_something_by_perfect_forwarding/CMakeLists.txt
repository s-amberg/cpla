#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}08_do_something_by_perfect_forwarding"
    "DoSomethingByPerfectForwarding.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}08_do_something_by_perfect_forwarding"
    PRIVATE
        "cpl::boost"
)
