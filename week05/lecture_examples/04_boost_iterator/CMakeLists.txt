#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}04_boost_iterator"
    "BoostIterator.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}04_boost_iterator"
    PRIVATE
    "cpl::boost"
)