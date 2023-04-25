add_executable("${CPL_TARGET_WEEK_PREFIX}02_seq_cst"
    "SeqCst.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}02_seq_cst" PRIVATE
    "Threads::Threads"
)
