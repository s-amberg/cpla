#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}09_int_inputter_with_pointers"
    "IntInputterWithPointers.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}09_int_inputter_with_pointers"
    PRIVATE
    "cpl::boost"
)