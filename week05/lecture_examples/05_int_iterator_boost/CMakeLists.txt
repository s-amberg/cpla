#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}05_int_iterator_boost"
    "IntIteratorBoost.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}05_int_iterator_boost"
    PRIVATE
    "cpl::boost"
)