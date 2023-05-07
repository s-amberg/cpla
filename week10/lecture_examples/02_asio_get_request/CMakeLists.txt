add_executable("${CPL_TARGET_WEEK_PREFIX}02_asio_get_request"
    "AsioGetRequest.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}02_asio_get_request" PRIVATE
    "Threads::Threads"
    "cpl::asio"
)
