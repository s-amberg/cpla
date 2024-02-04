#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}02_extract_middle"
    "ExtractMiddle.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}02_extract_middle"
    PRIVATE
    "cpl::boost"
)