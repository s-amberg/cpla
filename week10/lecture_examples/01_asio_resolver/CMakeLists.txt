add_executable("${CPL_TARGET_WEEK_PREFIX}01_asio_resolver"
    "AsioResolver.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}01_asio_resolver" PRIVATE
    "Threads::Threads"
    "cpl::asio"
)
