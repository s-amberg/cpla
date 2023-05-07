add_executable("${CPL_TARGET_WEEK_PREFIX}06_multi_run"
    "MultiRun.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}06_multi_run" PRIVATE
    "Threads::Threads"
    "cpl::asio"
)
