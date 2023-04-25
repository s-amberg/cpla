add_executable("${CPL_TARGET_WEEK_PREFIX}04_relaxed_memory_order"
    "RelaxedMemoryOrder.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}04_relaxed_memory_order" PRIVATE
    "Threads::Threads"
)
