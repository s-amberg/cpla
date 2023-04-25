add_executable("${CPL_TARGET_WEEK_PREFIX}00_non_atomic_flipper"
    "NonAtomicFlipper.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}00_non_atomic_flipper" PRIVATE
    "Threads::Threads"
)
