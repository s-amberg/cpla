add_executable("${CPL_TARGET_WEEK_PREFIX}05_custom_types"
    "CustomTypes.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}05_custom_types" PRIVATE
    "Threads::Threads"
)
