add_executable("${CPL_TARGET_WEEK_PREFIX}05_asio_signals"
    "AsioSignals.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}05_asio_signals" PRIVATE
    "Threads::Threads"
    "cpl::asio"
)
