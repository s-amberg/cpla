add_executable("${CPL_TARGET_WEEK_PREFIX}03_asio_sync_echo_server"
    "AsioSyncEchoServer.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}03_asio_sync_echo_server" PRIVATE
    "Threads::Threads"
    "cpl::asio"
)
