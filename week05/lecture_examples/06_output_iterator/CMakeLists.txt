#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}06_output_iterator"
    "OutputIterator.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}06_output_iterator"
    PRIVATE
    "cpl::boost"
)