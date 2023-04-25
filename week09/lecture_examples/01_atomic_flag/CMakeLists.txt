add_executable("${CPL_TARGET_WEEK_PREFIX}01_atomic_flag"
    "AtomicFlag.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}01_atomic_flag" PRIVATE
    "Threads::Threads"
)
