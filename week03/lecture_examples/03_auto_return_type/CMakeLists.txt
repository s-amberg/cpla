#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}03_auto_return_type"
    "AutoReturnType.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}03_auto_return_type"
    PRIVATE
    "cpl::boost"
)

